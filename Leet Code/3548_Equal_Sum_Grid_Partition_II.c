// ============================================================
// LeetCode 3548 - Equal Sum Grid Partition II
// PART 2: EDUCATIONAL VERSION  — how it works, behind the scenes
//
// Compile:  gcc -O2 -o lc3548 lc3548_part2_explained.c
// Run:      ./lc3548
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ============================================================
// VISUAL OVERVIEW
// ============================================================
//
//  grid = [[3,1,2],        total sum = 23
//          [4,2,3],
//          [1,5,2]]
//
//  ┌───┬───┬───┐
//  │ 3 │ 1 │ 2 │  ← top section after cut at row 0:  sum = 6
//  ╠═══╪═══╪═══╣  ← CUT HERE (horizontal cut after row 0)
//  │ 4 │ 2 │ 3 │  \
//  ├───┼───┼───┤   } bottom section sum = 17
//  │ 1 │ 5 │ 2 │  /
//  └───┴───┴───┘
//
//  top=6, bot=17, diff=11 → can we remove 11 from bottom? No.
//
//  ┌───┬───┬───┐
//  │ 3 │ 1 │ 2 │  \
//  ├───┼───┼───┤   } top section sum = 15
//  │ 4 │ 2 │ 3 │  /
//  ╠═══╪═══╪═══╣  ← CUT HERE (horizontal cut after row 1)
//  │ 1 │ 5 │ 2 │  ← bottom section sum = 8
//  └───┴───┴───┘
//
//  top=15, bot=8, diff=7 → can we remove 7 from top? No (7 not in top).
//
//  No horizontal cut works on this grid.
//  We would then try vertical cuts (by transposing and repeating).
//
// ============================================================


// ============================================================
// CONNECTIVITY RULE — the most subtle part of this problem
// ============================================================
//
// When sums differ by `diff`, we want to remove ONE cell of
// value `diff` from the heavier section. But that cell's
// removal must leave the section CONNECTED.
//
// CASE A — 2-D block  (rows > 1  AND  cols > 1)
//
//   ┌───┬───┬───┐
//   │   │   │   │   Any cell can be removed. Its neighbours
//   ├───┼───┼───┤   (up, down, left, right) keep everything
//   │   │ X │   │   reachable. ✓
//   ├───┼───┼───┤
//   │   │   │   │
//   └───┴───┴───┘
//
// CASE B — Single row  (rows == 1)
//
//   ┌───┬───┬───┬───┬───┐
//   │ X │   │   │   │ X │   Only the TWO END cells are safe.
//   └───┴───┴───┴───┴───┘   Removing a middle cell ─── splits!
//     ↑               ↑
//    col=0          col=n-1
//
// CASE C — Single column  (cols == 1)
//
//   ┌───┐
//   │ X │  ← row 0 of section (safe to remove)
//   ├───┤
//   │   │
//   ├───┤
//   │   │  ← middle cells are NOT safe (splits column)
//   ├───┤
//   │ X │  ← last row of section (safe to remove)
//   └───┘
//
// CASE D — Exactly 1×1
//   Removing the only cell leaves an EMPTY section → illegal.
//
// ============================================================


// ============================================================
// WHY A HASH MAP? — Efficient "does value V exist in section?"
// ============================================================
//
// Naively: scan the whole section for each cut → O(m*n) per cut
//          → O(m² * n) total. Too slow for 10^5 cells.
//
// Smart:   Keep TWO frequency maps (top_map, bot_map).
//          As we slide the cut downward one row at a time,
//          we MOVE that row's values from bot_map → top_map.
//          Each lookup is O(1) amortised.
//
//  Slide cut from top to bottom:
//
//  cut=0  top=[row0]          bot=[row1,row2]
//           ↓ move row1
//  cut=1  top=[row0,row1]     bot=[row2]
//           ↓ move row2  (but cut=m-2 is the last valid cut)
//
// ============================================================


// ============================================================
// HASH MAP IMPLEMENTATION (open-addressing, power-of-2 table)
// ============================================================

#define HM_CAP   131072          // 2^17 — enough for 10^5 cells
#define HM_MASK  (HM_CAP - 1)
#define HM_EMPTY (-1)            // sentinel: slot is unused

typedef struct { int key, val; } Entry;
typedef struct { Entry data[HM_CAP]; } HashMap;

// Reset every slot to EMPTY
static void hm_init(HashMap *h) {
    for (int i = 0; i < HM_CAP; i++) h->data[i].key = HM_EMPTY;
}

// Wang hash — spreads integer keys uniformly across the table
static inline int hm_hash(int k) {
    unsigned u = (unsigned)k;
    u ^= u >> 16;
    u *= 0x45d9f3b;
    u ^= u >> 16;
    return (int)(u & HM_MASK);
}

// Add `delta` to the count of `key` (inserts with count=0 first if new)
static void hm_add(HashMap *h, int key, int delta) {
    int idx = hm_hash(key);
    // Linear probe until we find the key or an empty slot
    while (h->data[idx].key != HM_EMPTY && h->data[idx].key != key)
        idx = (idx + 1) & HM_MASK;
    if (h->data[idx].key == HM_EMPTY) {
        h->data[idx].key = key;
        h->data[idx].val = 0;
    }
    h->data[idx].val += delta;
}

// Return count of `key`, or 0 if not found
static int hm_get(HashMap *h, int key) {
    int idx = hm_hash(key);
    while (h->data[idx].key != HM_EMPTY && h->data[idx].key != key)
        idx = (idx + 1) & HM_MASK;
    return (h->data[idx].key == HM_EMPTY) ? 0 : h->data[idx].val;
}


// ============================================================
// CAN WE REMOVE A CELL OF VALUE `diff` FROM THIS SECTION?
// ============================================================
//
// Parameters:
//   hm       → frequency map of the section
//   diff     → value we need to remove (must equal |top-bot|)
//   rows     → how many rows this section has
//   cols     → how many columns this section has
//   is_top   → true = section is above the cut line
//   cut_row  → index of the last row in the TOP section
//   grid     → original 2-D grid
//   m, n     → grid dimensions
// ============================================================
static bool can_remove(HashMap *hm, long long diff,
                       int rows, int cols,
                       bool is_top, int cut_row,
                       int **grid, int m, int n) {

    // Guard: diff must be a valid positive cell value
    if (diff <= 0 || diff > 1000000000LL) return false;

    // Guard: the value must actually exist in this section
    if (hm_get(hm, (int)diff) == 0) return false;

    // ── CASE A: 2-D block ───────────────────────────────────
    // Both dimensions > 1 → any cell can be safely removed.
    if (rows > 1 && cols > 1) return true;

    // ── CASE B: Single row ──────────────────────────────────
    // Only grid[r][0] or grid[r][n-1] can be removed.
    if (rows == 1) {
        int r = is_top ? cut_row : (cut_row + 1);
        //
        //  ┌───┬───┬───┬───┬───┐
        //  │ ? │   │   │   │ ? │   only ? positions are safe
        //  └───┴───┴───┴───┴───┘
        //  col=0              col=n-1
        //
        return (grid[r][0] == (int)diff || grid[r][n - 1] == (int)diff);
    }

    // ── CASE C: Single column ───────────────────────────────
    // Only the topmost or bottommost cell of the section.
    if (cols == 1) {
        int top_r    = is_top ? 0           : (cut_row + 1);
        int bottom_r = is_top ? cut_row     : (m - 1);
        //
        //  ┌───┐  ← top_r    (safe)
        //  ├───┤
        //  │   │  ← middle   (NOT safe — splits column)
        //  ├───┤
        //  └───┘  ← bottom_r (safe)
        //
        return (grid[top_r][0] == (int)diff || grid[bottom_r][0] == (int)diff);
    }

    // ── CASE D: 1×1 — removing the only cell → empty ────────
    return false;
}


// ============================================================
// CHECK ALL HORIZONTAL CUTS
// ============================================================
//
// We slide a virtual "cut line" downward, one row at a time.
//
//  Before the loop:
//    top_map is EMPTY,  bot_map has the FULL grid.
//    top_sum = 0.
//
//  Iteration i=0:  move row 0 from bot → top.
//    top = rows 0..0,   bot = rows 1..m-1
//
//  Iteration i=1:  move row 1 from bot → top.
//    top = rows 0..1,   bot = rows 2..m-1
//  ...
//
//  We stop at i = m-2  (cut must leave both sides non-empty).
// ============================================================
static bool check_horizontal(int **grid, int m, int n, long long total) {

    // Allocate on heap — these structs are large (~2 MB each)
    HashMap *top_map = (HashMap *)malloc(sizeof(HashMap));
    HashMap *bot_map = (HashMap *)malloc(sizeof(HashMap));
    hm_init(top_map);
    hm_init(bot_map);

    // Load the ENTIRE grid into bot_map
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            hm_add(bot_map, grid[i][j], +1);

    long long top_sum = 0;

    for (int i = 0; i < m - 1; i++) {

        // ── Step 1: Slide row i into the top section ────────
        //
        //   Before:  top=[0..i-1]   bot=[i..m-1]
        //   After:   top=[0..i]     bot=[i+1..m-1]
        //
        for (int j = 0; j < n; j++) {
            int v = grid[i][j];
            hm_add(top_map, v, +1);   // add to top
            hm_add(bot_map, v, -1);   // remove from bot
            top_sum += v;
        }
        long long bot_sum = total - top_sum;

        // ── Step 2: Compare the two sums ────────────────────
        //
        //   diff > 0 → top is heavier  → try removing diff from TOP
        //   diff < 0 → bot is heavier  → try removing -diff from BOT
        //   diff = 0 → already equal!
        //
        long long diff = top_sum - bot_sum;

        int top_rows = i + 1;          // rows 0..i
        int bot_rows = m - 1 - i;      // rows i+1..m-1

        if (diff == 0) {
            free(top_map); free(bot_map);
            return true;
        }

        if (diff > 0) {
            // Top is heavier: remove `diff` from top section
            if (can_remove(top_map, diff,
                           top_rows, n,
                           /*is_top=*/true, i,
                           grid, m, n)) {
                free(top_map); free(bot_map);
                return true;
            }
        } else {
            // Bottom is heavier: remove `-diff` from bottom section
            if (can_remove(bot_map, -diff,
                           bot_rows, n,
                           /*is_top=*/false, i,
                           grid, m, n)) {
                free(top_map); free(bot_map);
                return true;
            }
        }
    }

    free(top_map); free(bot_map);
    return false;
}


// ============================================================
// MAIN SOLVER
//
// Strategy:
//   1. Try all horizontal cuts.
//   2. Try all vertical cuts — by TRANSPOSING the grid and
//      reusing check_horizontal.
//      (A vertical cut on the original = horizontal cut on T)
//
//   Transposing avoids duplicating all the cut logic.
// ============================================================
bool canPartitionGrid(int **grid, int gridSize, int *gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];

    // Total sum of all cells
    long long total = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            total += grid[i][j];

    // ── Horizontal cuts ─────────────────────────────────────
    if (check_horizontal(grid, m, n, total)) return true;

    // ── Vertical cuts (via transpose) ───────────────────────
    //
    //  Original:          Transpose T:
    //  ┌─┬─┬─┐            ┌─┬─┬─┐
    //  │a│b│c│            │a│d│g│
    //  ├─┼─┼─┤  ──────►   ├─┼─┼─┤
    //  │d│e│f│            │b│e│h│
    //  ├─┼─┼─┤            ├─┼─┼─┤
    //  │g│h│i│            │c│f│i│
    //  └─┴─┴─┘            └─┴─┴─┘
    //   3×3 grid            3×3 transpose
    //
    //  A vertical cut after column j in the original
    //  = horizontal cut after row j in the transpose.
    //
    int **T = (int **)malloc(n * sizeof(int *));
    for (int j = 0; j < n; j++) {
        T[j] = (int *)malloc(m * sizeof(int));
        for (int i = 0; i < m; i++)
            T[j][i] = grid[i][j];     // T[j][i] = original[i][j]
    }

    int T_colSize = m;
    bool ans = check_horizontal(T, n, m, total);

    for (int j = 0; j < n; j++) free(T[j]);
    free(T);

    return ans;
}


// ============================================================
// HELPER — build a 2-D grid from a flat array for testing
// ============================================================
static int **make_grid(int flat[], int m, int n) {
    int **g = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        g[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            g[i][j] = flat[i * n + j];
    }
    return g;
}

static void free_grid(int **g, int m) {
    for (int i = 0; i < m; i++) free(g[i]);
    free(g);
}

static void print_grid(int **g, int m, int n) {
    for (int i = 0; i < m; i++) {
        printf("  [ ");
        for (int j = 0; j < n; j++) printf("%d ", g[i][j]);
        printf("]\n");
    }
}


// ============================================================
// MAIN — test cases with expected outputs
// ============================================================
int main(void) {

    printf("==============================================\n");
    printf("  LeetCode 3548 — Equal Sum Grid Partition II\n");
    printf("==============================================\n\n");

    // ----------------------------------------------------------
    // TEST 1: grid = [[1,4],[2,3]]
    //
    //   ┌───┬───┐
    //   │ 1 │ 4 │  top sum = 5
    //   ╠═══╪═══╣  ← horizontal cut after row 0
    //   │ 2 │ 3 │  bot sum = 5  ✓ Equal!
    //   └───┴───┘
    //
    //   Expected: true
    // ----------------------------------------------------------
    {
        int flat[] = {1,4, 2,3};
        int m=2, n=2;
        int **g = make_grid(flat, m, n);
        int cs[] = {n};
        printf("Test 1: grid =\n"); print_grid(g, m, n);
        bool res = canPartitionGrid(g, m, cs);
        printf("  Result: %s  (expected: true)\n\n", res ? "true" : "false");
        free_grid(g, m);
    }

    // ----------------------------------------------------------
    // TEST 2: grid = [[1,3],[2,2],[1,5],[2,3]]
    //
    //   ┌───┬───┐
    //   │ 1 │ 3 │  \
    //   ├───┼───┤   } top = 9
    //   │ 2 │ 2 │  /
    //   ╠═══╪═══╣  ← cut after row 1
    //   │ 1 │ 5 │  \
    //   ├───┼───┤   } bot = 11
    //   │ 2 │ 3 │  /
    //   └───┴───┘
    //
    //   diff = 9 - 11 = -2  → need to remove 2 from BOTTOM.
    //   Bottom is 2×2, so any cell works.  Value 2 exists? YES.
    //   → true
    //
    //   Expected: true
    // ----------------------------------------------------------
    {
        int flat[] = {1,3, 2,2, 1,5, 2,3};
        int m=4, n=2;
        int **g = make_grid(flat, m, n);
        int cs[] = {n};
        printf("Test 2: grid =\n"); print_grid(g, m, n);
        bool res = canPartitionGrid(g, m, cs);
        printf("  Result: %s  (expected: true)\n\n", res ? "true" : "false");
        free_grid(g, m);
    }

    // ----------------------------------------------------------
    // TEST 3: grid = [[1,2],[3,4]]
    //
    //   ┌───┬───┐
    //   │ 1 │ 2 │  top = 3
    //   ╠═══╪═══╣
    //   │ 3 │ 4 │  bot = 7   diff=4 → remove 4? Not in top.
    //   └───┴───┘             remove 4 from bot (1 row)? grid[1][0]=3≠4,
    //                          grid[1][1]=4=4 ✓  BUT: wait...
    //   Actually diff = 3-7 = -4 → need 4 from BOT (single row).
    //   grid[1][0]=3, grid[1][1]=4  → end cell 4 == 4 ✓  → true!
    //
    //   Wait — let's also try vertical cut after col 0:
    //   left=[1,3]=4, right=[2,4]=6, diff=-2, remove 2 from right.
    //   Right is a single column: top=grid[0][1]=2==2 ✓ → true!
    //
    //   Expected: true
    // ----------------------------------------------------------
    {
        int flat[] = {1,2, 3,4};
        int m=2, n=2;
        int **g = make_grid(flat, m, n);
        int cs[] = {n};
        printf("Test 3: grid =\n"); print_grid(g, m, n);
        bool res = canPartitionGrid(g, m, cs);
        printf("  Result: %s  (expected: true)\n\n", res ? "true" : "false");
        free_grid(g, m);
    }

    // ----------------------------------------------------------
    // TEST 4: grid = [[7,2],[3,10]]
    //
    //   Horizontal cut after row 0:
    //     top=9, bot=13, diff=-4 → remove 4? Not in bot (has 3,10).
    //   Vertical cut after col 0:
    //     left=10, right=12, diff=-2 → remove 2 from right.
    //     Right is single col: top=grid[0][1]=2==2 ✓ → true!
    //
    //   Expected: true
    // ----------------------------------------------------------
    {
        int flat[] = {7,2, 3,10};
        int m=2, n=2;
        int **g = make_grid(flat, m, n);
        int cs[] = {n};
        printf("Test 4: grid =\n"); print_grid(g, m, n);
        bool res = canPartitionGrid(g, m, cs);
        printf("  Result: %s  (expected: true)\n\n", res ? "true" : "false");
        free_grid(g, m);
    }

    // ----------------------------------------------------------
    // TEST 5: grid = [[1],[2],[3],[5]]
    //
    //   Single column, horizontal cuts only (vertical cut needs n≥2).
    //
    //   Cut after row 0: top=[1]=1,  bot=[2,3,5]=10, diff=-9 → remove 9? No.
    //   Cut after row 1: top=[1,2]=3, bot=[3,5]=8,   diff=-5 → remove 5 from bot.
    //     Bot is 2 rows × 1 col → CASE C.
    //     top_r of bot section = row 2 → grid[2][0]=3 ≠ 5
    //     bot_r of bot section = row 3 → grid[3][0]=5 == 5  ✓ → true!
    //
    //   Expected: true
    // ----------------------------------------------------------
    {
        int flat[] = {1,2,3,5};
        int m=4, n=1;
        int **g = make_grid(flat, m, n);
        int cs[] = {n};
        printf("Test 5: grid =\n"); print_grid(g, m, n);
        bool res = canPartitionGrid(g, m, cs);
        printf("  Result: %s  (expected: true)\n\n", res ? "true" : "false");
        free_grid(g, m);
    }

    // ----------------------------------------------------------
    // TEST 6: grid = [[5,5]]   (1 row — only vertical cuts)
    //
    //   Vertical cut after col 0:
    //     left=[5]=5, right=[5]=5, diff=0 → EQUAL ✓
    //
    //   Expected: true
    // ----------------------------------------------------------
    {
        int flat[] = {5,5};
        int m=1, n=2;
        int **g = make_grid(flat, m, n);
        int cs[] = {n};
        printf("Test 6: grid =\n"); print_grid(g, m, n);
        bool res = canPartitionGrid(g, m, cs);
        printf("  Result: %s  (expected: true)\n\n", res ? "true" : "false");
        free_grid(g, m);
    }

    // ----------------------------------------------------------
    // TEST 7: grid = [[1,1],[1,1]]
    //
    //   Horizontal cut after row 0: top=2, bot=2, diff=0 → EQUAL ✓
    //
    //   Expected: true
    // ----------------------------------------------------------
    {
        int flat[] = {1,1, 1,1};
        int m=2, n=2;
        int **g = make_grid(flat, m, n);
        int cs[] = {n};
        printf("Test 7: grid =\n"); print_grid(g, m, n);
        bool res = canPartitionGrid(g, m, cs);
        printf("  Result: %s  (expected: true)\n\n", res ? "true" : "false");
        free_grid(g, m);
    }

    // ----------------------------------------------------------
    // TEST 8 (tricky — middle removal in single row NOT allowed):
    //
    //   grid = [[1,3,2,2,1]]   (1 row, 5 cols)
    //   total = 9
    //
    //   Vertical cut after col 0: left=1, right=8, diff=-7 → remove 7? No.
    //   Vertical cut after col 1: left=4, right=5, diff=-1 → remove 1 from right.
    //     Right section is 1 row: [2,2,1]. End cells: 2 and 1.
    //     diff=1 → grid[0][2]=2≠1, grid[0][4]=1==1 ✓ → true
    //
    //   Expected: true
    // ----------------------------------------------------------
    {
        int flat[] = {1,3,2,2,1};
        int m=1, n=5;
        int **g = make_grid(flat, m, n);
        int cs[] = {n};
        printf("Test 8: grid =\n"); print_grid(g, m, n);
        bool res = canPartitionGrid(g, m, cs);
        printf("  Result: %s  (expected: true)\n\n", res ? "true" : "false");
        free_grid(g, m);
    }

    printf("==============================================\n");
    printf("  All tests done.\n");
    printf("==============================================\n");
    return 0;
}

// ============================================================
// COMPLEXITY ANALYSIS
// ============================================================
//
//  Let N = m * n  (total number of cells, ≤ 10^5)
//
//  TIME:
//    check_horizontal runs in O(m * n) = O(N)
//      - Outer loop:  m-1 iterations
//      - Inner loop:  n cells moved per iteration
//      - Each hm_add / hm_get:  O(1) amortised
//    Building transpose T: O(N)
//    check_horizontal on T: O(N)
//    Total: O(N)
//
//  SPACE:
//    Two HashMaps: 2 × HM_CAP × 8 bytes ≈ 2 MB each → 4 MB total
//    Transpose T: O(N)
//    Total: O(N)
//
// ============================================================
//
// EDGE CASES HANDLED:
//   • 1×n grid (single row) — only vertical cuts possible
//   • m×1 grid (single col) — only horizontal cuts possible
//   • 1×1 grid             — no valid cut (both sections must be non-empty)
//   • diff == 0            — immediate true, no removal needed
//   • diff not in section  — false for that cut
//   • Single-row/col section with diff at non-edge cell → false
//
// ============================================================
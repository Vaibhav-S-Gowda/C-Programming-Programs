#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int r, c, rem, steps;
} Node;

/**
 * Solves LeetCode 1293: Shortest Path in a Grid with Obstacles Elimination.
 * Uses BFS with an optimized 2D visited array tracking maximum 'k' remaining.
 */
int shortestPath(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize;
    int n = gridColSize[0];

    // 1. Instant Exit: 1x1 grid
    if (m == 1 && n == 1) return 0;

    // 2. Global Shortcut: If k is enough to take any Manhattan path
    if (k >= (m + n - 2)) return m + n - 2;

    // 3. Optimized Visited Array: Store the max 'rem' found for each (r, c)
    // Initialize with -1 (unvisited)
    int* max_rem_at = (int*)malloc(m * n * sizeof(int));
    for (int i = 0; i < m * n; i++) max_rem_at[i] = -1;

    // 4. Queue Setup: Circular buffer
    // Max states to explore is roughly m*n, but we use a safe buffer
    int q_capacity = m * n * (k + 1);
    Node* queue = (Node*)malloc(q_capacity * sizeof(Node));
    int head = 0, tail = 0;

    // Initial State
    queue[tail++] = (Node){0, 0, k, 0};
    max_rem_at[0] = k;

    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};

    while (head < tail) {
        Node cur = queue[head++];
        
        // Per-cell Manhattan Shortcut: Can we go straight to the end?
        int dist_to_end = (m - 1 - cur.r) + (n - 1 - cur.c);
        if (cur.rem >= dist_to_end) {
            int result = cur.steps + dist_to_end;
            free(max_rem_at); free(queue);
            return result;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];

            // Bounds Check
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;

            int nrem = cur.rem - grid[nr][nc];

            // Pruning: Only proceed if we have removals left AND this path 
            // is "better" (more removals left) than any previous path to this cell.
            if (nrem >= 0 && max_rem_at[nr * n + nc] < nrem) {
                max_rem_at[nr * n + nc] = nrem;
                queue[tail++] = (Node){nr, nc, nrem, cur.steps + 1};
            }
        }
    }

    free(max_rem_at);
    free(queue);
    return -1;
}

/* ─── Test Harness ────────────────────────────────────────────────────────── */

/*
 * HOW TO BUILD & RUN:
 *   gcc -O2 -o lc1293 lc1293_shortest_path_grid.c && ./lc1293
 *
 * Expected output:
 *   Test 1: 6   (LeetCode example 1)
 *   Test 2: -1  (LeetCode example 2)
 *   Test 3: 0   (1x1 grid)
 *   Test 4: 2   (2x2, k>=manhattan shortcut)
 */
int main(void) {

    /* ─── Test 1: 3×3, k=1 ────────────────────────────────────────────── */
    /* Grid:
     *   0 0 0
     *   1 1 0
     *   0 0 0
     *   0 1 1
     *   0 0 0
     * Answer: 6 (go around obstacles, eliminate one)
     */
    int r1c = 3;
    int g1r0[] = {0,0,0}, g1r1[] = {1,1,0}, g1r2[] = {0,0,0},
        g1r3[] = {0,1,1}, g1r4[] = {0,0,0};
    int *g1[] = {g1r0, g1r1, g1r2, g1r3, g1r4};
    int g1cols[] = {r1c, r1c, r1c, r1c, r1c};
    printf("Test 1: %d  (expected 6)\n",  shortestPath(g1, 5, g1cols, 1));

    /* ─── Test 2: LeetCode example 2 — 3×3, k=1, completely blocked ───── */
    /* Grid:
     *   0 1 1
     *   1 1 1
     *   1 0 0
     * Every path from (0,0) to (2,2) requires removing ≥2 obstacles,
     * but k=1 → impossible.
     */
    int r2c = 3;
    int g2r0[] = {0,1,1}, g2r1[] = {1,1,1}, g2r2[] = {1,0,0};
    int *g2[] = {g2r0, g2r1, g2r2};
    int g2cols[] = {r2c, r2c, r2c};
    printf("Test 2: %d  (expected -1)\n", shortestPath(g2, 3, g2cols, 1));

    /* ─── Test 3: 1×1 grid ───────────────────────────────────────────── */
    int g3r0[] = {0};
    int *g3[] = {g3r0};
    int g3cols[] = {1};
    printf("Test 3: %d  (expected 0)\n",  shortestPath(g3, 1, g3cols, 0));

    /* ─── Test 4: 2×2, k=10 (manhattan shortcut fires immediately) ──── */
    int g4r0[] = {0,1}, g4r1[] = {1,0};
    int *g4[] = {g4r0, g4r1};
    int g4cols[] = {2, 2};
    printf("Test 4: %d  (expected 2)\n",  shortestPath(g4, 2, g4cols, 10));

    return 0;
}

// ┌─────────────────────────────────────────────────────────┐
// │         LeetCode 1293 — BFS Algorithm Flow              │
// └─────────────────────────────────────────────────────────┘

//          ┌──────────────────────────────┐
//          │    START: enqueue (0,0,k,0)  │
//          └──────────────┬───────────────┘
//                         │
//                         ▼
//          ┌──────────────────────────────┐
//          │   k >= (m-1)+(n-1)?          │  ← Global manhattan
//          │   (shortcut before BFS)      │    shortcut check
//          └──────┬───────────────┬───────┘
//           YES   │               │  NO
//                 ▼               │
//     ┌───────────────────┐       │
//     │ return manhattan  │       │
//     └───────────────────┘       │
//                                 ▼
//          ╔══════════════════════════════╗
//          ║        BFS LOOP              ║
//          ║  ┌────────────────────────┐  ║
//          ║  │  Queue empty?          │  ║
//          ║  └────┬──────────────┬────┘  ║
//          ║  YES  │              │  NO   ║
//          ║       │              ▼       ║
//          ║       │  ┌─────────────────┐ ║
//          ║       │  │ Dequeue front:  │ ║
//          ║       │  │ (r,c,rem,steps) │ ║
//          ║       │  └────────┬────────┘ ║
//          ║       │           │          ║
//          ║       │           ▼          ║
//          ║       │  ┌─────────────────┐ ║
//          ║       │  │ rem >= dist to  │ ║  ← Per-cell manhattan
//          ║       │  │    goal?        │ ║    shortcut (mid-BFS)
//          ║       │  └──┬──────────┬───┘ ║
//          ║       │ YES │          │ NO  ║
//          ║       │     ▼          │     ║
//          ║       │  ┌──────────┐  │     ║
//          ║       │  │  return  │  │     ║
//          ║       │  │steps+dist│  │     ║
//          ║       │  └──────────┘  │     ║
//          ║       │                ▼     ║
//          ║       │  ┌─────────────────┐ ║
//          ║       │  │ For each of 4   │ ║
//          ║       │  │   neighbors     │ ║
//          ║       │  └────────┬────────┘ ║
//          ║       │           │          ║
//          ║       │           ▼          ║
//          ║       │  ┌─────────────────┐ ║
//          ║       │  │ Out of bounds?  │ ║
//          ║       │  │ nrem < 0?       ├─╫──► SKIP
//          ║       │  │ Already visited?│ ║
//          ║       │  └────────┬────────┘ ║
//          ║       │      PASS │          ║
//          ║       │           ▼          ║
//          ║       │  ┌─────────────────┐ ║
//          ║       │  │ Mark visited    │ ║
//          ║       │  │ (nr,nc,nrem)=1  │ ║
//          ║       │  └────────┬────────┘ ║
//          ║       │           │          ║
//          ║       │           ▼          ║
//          ║       │  ┌─────────────────┐ ║
//          ║       │  │ Enqueue         │ ║
//          ║       │  │(nr,nc,nrem,st+1)│ ║
//          ║       │  └────────┬────────┘ ║
//          ║       │           │          ║
//          ║       │           └──────────╫──► (back to loop top)
//          ║       │                      ║
//          ╚═══════╪══════════════════════╝
//                  │
//                  ▼
//          ┌───────────────────┐
//          │    return -1      │  ← No path exists
//          └───────────────────┘

// ┌─────────────────────────────────────────────────────────┐
// │  STATE SPACE KEY                                        │
// │                                                         │
// │  State  = (row, col, rem)                               │
// │  nrem   = rem - grid[nr][nc]   ← costs 1 if obstacle    │
// │  dist   = |r-(m-1)| + |c-(n-1)|                         │
// │  visited[r][c][rem] prevents revisiting same state      │
// │                                                         │
// │  Complexity: Time O(m·n·k)  |  Space O(m·n·k)           │
// └─────────────────────────────────────────────────────────┘
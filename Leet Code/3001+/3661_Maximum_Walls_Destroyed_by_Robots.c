/* ============================================================
   LEETCODE 3661 — Maximum Walls Destroyed by Robots
   ============================================================
   PROBLEM SUMMARY:
   - Robots and walls sit on an infinite number line.
   - Each robot fires ONE bullet: left OR right, up to distance[i].
   - A bullet STOPS if it hits another robot's body first.
   - Goal: choose a direction per robot to maximize UNIQUE walls hit.

   APPROACH: Memoised DFS + Binary Search
   - Sort robots by position (left to right).
   - Process robots right-to-left via DFS.
   - dfs(i, j):
       i = index of current robot being decided
       j = direction the robot to the RIGHT of i already fired
           0 → right neighbour fired LEFT  (its bullet comes toward i)
           1 → right neighbour fired RIGHT (no left-side intrusion)
   - For each robot, try both directions, pick the better score.
   - Use binary search on sorted walls to count walls in any range fast.
   - Memoize on (i, j) → only 2n states total.

   TIME : O(n log n + m log m + n log m)
           n = number of robots, m = number of walls
   SPACE: O(n)  — memo table of size 2n
   ============================================================ */


#include <stdio.h>
#include <stdlib.h>

/* ══════════════════════════════════════════════════════════════════
   HELPERS
   ══════════════════════════════════════════════════════════════════ */

static int lower_bound(int *w, int len, int target) {
    int lo = 0, hi = len;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (w[mid] < target) lo = mid + 1;
        else                 hi = mid;
    }
    return lo;
}

static int upper_bound(int *w, int len, int target) {
    int lo = 0, hi = len;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (w[mid] <= target) lo = mid + 1;
        else                  hi = mid;
    }
    return lo;
}

/* Walls in closed range [L, R] */
static int count_walls(int *w, int len, int L, int R) {
    if (L > R) return 0;
    return upper_bound(w, len, R) - lower_bound(w, len, L);
}

static int cmp_pair(const void *a, const void *b) {
    return ((const int *)a)[0] - ((const int *)b)[0];
}
static int cmp_int(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

/* ══════════════════════════════════════════════════════════════════
   GLOBALS (simulate what LeetCode's solution-only file would have
   as statics — here exposed for trace printing)
   ══════════════════════════════════════════════════════════════════ */
static int  (*g_arr)[2];
static int   g_n;
static int  *g_walls;
static int   g_wLen;
static int  *g_memo;

/* ══════════════════════════════════════════════════════════════════
   DFS WITH TRACE
   ══════════════════════════════════════════════════════════════════ */
static int dfs_trace(int i, int j, int depth) {
    /* Indent for readability */
    for (int d = 0; d < depth; d++) printf("  ");

    if (i < 0) {
        printf("dfs(%d,%d) → base case → 0\n", i, j);
        return 0;
    }

    int key = i * 2 + j;
    if (g_memo[key] != -1) {
        printf("dfs(i=%d,j=%d) → memo hit → %d\n", i, j, g_memo[key]);
        return g_memo[key];
    }

    printf("dfs(i=%d [pos=%d,dist=%d], j=%d)\n",
           i, g_arr[i][0], g_arr[i][1], j);

    int pos  = g_arr[i][0];
    int dist = g_arr[i][1];

    /* ── FIRE LEFT ─────────────────────────── */
    int leftL = pos - dist;
    if (i > 0 && g_arr[i-1][0] + 1 > leftL)
        leftL = g_arr[i-1][0] + 1;

    int wallsA = count_walls(g_walls, g_wLen, leftL, pos);
    for (int d = 0; d < depth+1; d++) printf("  ");
    printf("← Fire LEFT:  range [%d, %d], walls hit = %d\n", leftL, pos, wallsA);

    int scoreA = dfs_trace(i - 1, 0, depth + 1) + wallsA;

    /* ── FIRE RIGHT ────────────────────────── */
    int rightR = pos + dist;
    if (i + 1 < g_n) {
        int nextPos  = g_arr[i+1][0];
        int nextDist = g_arr[i+1][1];
        int cap = (j == 0) ? nextPos - nextDist - 1 : nextPos - 1;
        if (cap < rightR) rightR = cap;
    }
    int wallsB = count_walls(g_walls, g_wLen, pos, rightR);
    for (int d = 0; d < depth+1; d++) printf("  ");
    printf("→ Fire RIGHT: range [%d, %d], walls hit = %d\n", pos, rightR, wallsB);

    int scoreB = dfs_trace(i - 1, 1, depth + 1) + wallsB;

    int best = scoreA > scoreB ? scoreA : scoreB;
    for (int d = 0; d < depth; d++) printf("  ");
    printf("dfs(i=%d,j=%d) best = max(L:%d, R:%d) = %d\n", i, j, scoreA, scoreB, best);

    g_memo[key] = best;
    return best;
}

/* ══════════════════════════════════════════════════════════════════
   MAIN ENTRY (maxWalls wrapper)
   ══════════════════════════════════════════════════════════════════ */
static int maxWalls(int *robots, int n,
                    int *distance, int dn,
                    int *walls,    int wLen) {
    int (*arr)[2] = malloc(n * sizeof(*arr));
    for (int i = 0; i < n; i++) { arr[i][0] = robots[i]; arr[i][1] = distance[i]; }
    qsort(arr, n, sizeof(*arr), cmp_pair);

    int *sortedWalls = malloc(wLen * sizeof(int));
    for (int i = 0; i < wLen; i++) sortedWalls[i] = walls[i];
    qsort(sortedWalls, wLen, sizeof(int), cmp_int);

    int *memo = malloc(n * 2 * sizeof(int));
    for (int i = 0; i < n * 2; i++) memo[i] = -1;

    g_arr   = arr;
    g_n     = n;
    g_walls = sortedWalls;
    g_wLen  = wLen;
    g_memo  = memo;

    printf("\nSorted robots (pos, dist): ");
    for (int i = 0; i < n; i++) printf("[%d,%d] ", arr[i][0], arr[i][1]);
    printf("\nSorted walls: ");
    for (int i = 0; i < wLen; i++) printf("%d ", sortedWalls[i]);
    printf("\n\n--- DFS Trace ---\n");

    int ans = dfs_trace(n - 1, 1, 0);

    free(arr); free(sortedWalls); free(memo);
    return ans;
}

/* ══════════════════════════════════════════════════════════════════
   TEST DRIVER
   ══════════════════════════════════════════════════════════════════ */
int main(void) {

    /* Example 1: robots=[5], distance=[3], walls=[4,8] → expected 1 */
    printf("=== Example 1 ===\n");
    int r1[] = {5}, d1[] = {3}, w1[] = {4, 8};
    printf("Answer: %d  (expected 1)\n\n",
           maxWalls(r1,1, d1,1, w1,2));

    /* Example 2: robots=[10,2], distance=[5,1], walls=[5,2,7] → expected 3 */
    printf("=== Example 2 ===\n");
    int r2[] = {10,2}, d2[] = {5,1}, w2[] = {5,2,7};
    printf("Answer: %d  (expected 3)\n\n",
           maxWalls(r2,2, d2,2, w2,3));

    /* Example 3: robots=[1,2], distance=[100,1], walls=[10] → expected 0 */
    printf("=== Example 3 ===\n");
    int r3[] = {1,2}, d3[] = {100,1}, w3[] = {10};
    printf("Answer: %d  (expected 0)\n\n",
           maxWalls(r3,2, d3,2, w3,1));

    return 0;
}

/*
 * ================================================================
 *  HOW dfs(i, j) WORKS — VISUAL DIAGRAM
 * ================================================================
 *
 *  NUMBER LINE (Example 2: robots=[2,10], dist=[1,5], walls=[2,5,7])
 *  After sorting robots by position:
 *
 *  pos:   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
 *         |   |   |   |   |   |   |   |   |   |   |
 *            [R0]           [W] [W]           [R1]
 *             pos=2          5   7             pos=10
 *             dist=1                           dist=5
 *         [W]
 *          2
 *
 *  Robots are processed RIGHT TO LEFT by DFS (i = n-1 down to 0).
 *  We start with dfs(i = n-1, j = 1).
 *  j = 1 is a sentinel meaning "no right neighbour constraining us".
 *
 * ================================================================
 *  DFS CALL TREE
 * ================================================================
 *
 *                    dfs(i=1, j=1)
 *                   [R1 at pos=10]
 *                  /              \
 *          fire LEFT              fire RIGHT
 *         range[5,10]            range[10,14]
 *          +2 walls               +0 walls
 *               |                      |
 *               v                      v
 *        dfs(i=0, j=0)          dfs(i=0, j=1)
 *       [R0 at pos=2]          [R0 at pos=2]
 *        /         \            /           \
 *    fire←        fire→     fire←          fire→
 *   [1,2]    capped early   [1,2]        [2, R1.pos-1]
 *   +1 wall  at R1.left-1   +1 wall      = [2,9] → +0walls
 *            = [2,4] +0                  (wall at 5,7 are
 *                                         in R1's zone)
 *
 *  FINAL SCORES:
 *  Path A: R1 fires LEFT  (+2) + R0 fires LEFT  (+1) = 3  ← BEST
 *  Path B: R1 fires RIGHT (+0) + R0 fires LEFT  (+1) = 1
 *
 * ================================================================
 *  WHY j MATTERS (the direction the RIGHT neighbour fired)
 * ================================================================
 *
 *  When robot i fires RIGHT, its bullet can be blocked by either:
 *    (a) The BODY of robot i+1            → always blocks at i+1.pos - 1
 *    (b) The BULLET of robot i+1 (if i+1
 *        fired LEFT, its bullet is flying
 *        toward us and blocks us earlier) → blocks at i+1.pos - i+1.dist - 1
 *
 *  So the right cap depends on what i+1 chose:
 *
 *    j == 1  (right neighbour fired RIGHT, bullet going away from us):
 *            right_cap = arr[i+1].pos - 1          (only body blocks)
 *
 *    j == 0  (right neighbour fired LEFT, bullet coming at us):
 *            right_cap = arr[i+1].pos - arr[i+1].dist - 1  (bullet blocks earlier)
 *
 *  Firing LEFT is never affected by j — the left neighbour's
 *  body always blocks at arr[i-1].pos + 1 regardless.
 *
 * ================================================================
 *  MEMO TABLE  (size = n * 2)
 * ================================================================
 *
 *    memo[i][0] = best walls destroyable by robots 0..i
 *                 when robot i+1 fired LEFT  (j=0)
 *
 *    memo[i][1] = best walls destroyable by robots 0..i
 *                 when robot i+1 fired RIGHT (j=1)
 *
 *    Stored flat as:  g_memo[i * 2 + j]
 *    Initialised to:  -1  (means "not yet computed")
 *
 *    Only 2n states exist because each robot has exactly
 *    2 possible j-values from its right neighbour.
 *
 * ================================================================
 *  BINARY SEARCH TRICK (counting walls in a range)
 * ================================================================
 *
 *  walls[] is sorted once at the start.
 *  To count walls in closed range [L, R]:
 *
 *    walls:  [ 2,  5,  7,  9, 12 ]
 *               ^           ^
 *           lower_bound(L) upper_bound(R)
 *
 *    count  = upper_bound(R) - lower_bound(L)
 *           = (index of first wall > R)
 *           - (index of first wall >= L)
 *
 *  This runs in O(log m) instead of O(m) per range query.
 *
 * ================================================================
 *  CALL FLOW SUMMARY
 * ================================================================
 *
 *  maxWalls()
 *    │
 *    ├─ sort robots by position  → arr[0..n-1]
 *    ├─ sort walls               → walls[0..m-1]
 *    ├─ init memo[0..2n-1] = -1
 *    │
 *    └─ return dfs(n-1, j=1)
 *                │
 *                ├─ base case: i < 0 → return 0
 *                ├─ memo hit:         → return memo[i*2+j]
 *                │
 *                ├─ OPTION A (fire LEFT):
 *                │    left  = max(arr[i].pos - arr[i].dist,
 *                │                arr[i-1].pos + 1)   ← body blocks
 *                │    count = walls in [left, arr[i].pos]
 *                │    scoreA = dfs(i-1, j=0) + count
 *                │
 *                ├─ OPTION B (fire RIGHT):
 *                │    right = arr[i].pos + arr[i].dist
 *                │    if j==0: right = min(right, arr[i+1].pos - arr[i+1].dist - 1)
 *                │    if j==1: right = min(right, arr[i+1].pos - 1)
 *                │    count = walls in [arr[i].pos, right]
 *                │    scoreB = dfs(i-1, j=1) + count
 *                │
 *                └─ memo[i*2+j] = max(scoreA, scoreB)
 *
 * ================================================================
 */
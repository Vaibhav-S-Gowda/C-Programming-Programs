#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007LL
// Inline max/min to avoid function call overhead
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

int maxProductPath(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];

    /*
     * Use two flat 1D arrays instead of 2D DP arrays.
     * Flat arrays = better cache locality, no pointer indirection.
     * We only need current row and previous row → O(n) space.
     */
    long long* dpMax = (long long*)malloc(n * sizeof(long long));
    long long* dpMin = (long long*)malloc(n * sizeof(long long));

    // ── Seed: top-left cell ──
    dpMax[0] = dpMin[0] = grid[0][0];

    // ── First row: can only come from the left ──
    for (int j = 1; j < n; j++) {
        long long v = grid[0][j];
        long long prev_max = dpMax[j-1];
        long long prev_min = dpMin[j-1];
        long long a = prev_max * v;
        long long b = prev_min * v;
        dpMax[j] = MAX(a, b);
        dpMin[j] = MIN(a, b);
    }

    // ── Remaining rows ──
    for (int i = 1; i < m; i++) {
        int* row = grid[i];   // cache row pointer — avoids repeated grid[i] dereference

        // First column: can only come from above
        {
            long long v  = row[0];
            long long a  = dpMax[0] * v;
            long long b  = dpMin[0] * v;
            dpMax[0] = MAX(a, b);
            dpMin[0] = MIN(a, b);
        }

        // Remaining columns: take best of (from left, from above)
        for (int j = 1; j < n; j++) {
            long long v    = row[j];
            long long lMax = dpMax[j-1] * v;   // from left  × v
            long long lMin = dpMin[j-1] * v;
            long long uMax = dpMax[j]   * v;   // from above × v
            long long uMin = dpMin[j]   * v;

            // Best achievable max and min at (i,j)
            dpMax[j] = MAX(MAX(lMax, lMin), MAX(uMax, uMin));
            dpMin[j] = MIN(MIN(lMax, lMin), MIN(uMax, uMin));
        }
    }

    long long ans = dpMax[n-1];

    free(dpMax);
    free(dpMin);

    if (ans < 0) return -1;
    return (int)(ans % MOD);
}

int main() {
    int m, n;

    // Input grid size
    printf("Enter rows and columns: ");
    scanf("%d %d", &m, &n);

    // Allocate grid
    int** grid = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        grid[i] = (int*)malloc(n * sizeof(int));
    }

    // Input grid values
    printf("Enter grid values:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Column size array (LeetCode style)
    int* gridColSize = (int*)malloc(sizeof(int));
    gridColSize[0] = n;

    // Call function
    int result = maxProductPath(grid, m, gridColSize);

    // Output result
    printf("Maximum Product Path: %d\n", result);

    // Free memory
    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }
    free(grid);
    free(gridColSize);

    return 0;
}
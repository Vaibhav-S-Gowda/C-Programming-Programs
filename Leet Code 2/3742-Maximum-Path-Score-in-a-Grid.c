#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int maxPathScore(int** grid, int gridSize, int* gridColSize, int k) {
    int rows = gridSize;
    int cols = *gridColSize;

    // dp[i][j][c] stores the max score at cell (i,j) with cost c
    // We use a pointer-based 3D array or a flat array to handle dynamic sizes
    int dp[rows][cols][k + 1];

    // Initialize with -1 (unreachable)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int c = 0; c <= k; c++) {
                dp[i][j][c] = -1;
            }
        }
    }

    // Starting point (0, 0)
    // Cost is 1 if grid[0][0] > 0, otherwise 0
    int startCost = (grid[0][0] > 0) ? 1 : 0;
    if (startCost <= k) {
        dp[0][0][startCost] = grid[0][0];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int c = 0; c <= k; c++) {
                if (dp[i][j][c] == -1) continue;

                // Move Right
                if (j + 1 < cols) {
                    int nextCost = c + (grid[i][j + 1] > 0 ? 1 : 0);
                    if (nextCost <= k) {
                        dp[i][j + 1][nextCost] = MAX(dp[i][j + 1][nextCost], dp[i][j][c] + grid[i][j + 1]);
                    }
                }

                // Move Down
                if (i + 1 < rows) {
                    int nextCost = c + (grid[i + 1][j] > 0 ? 1 : 0);
                    if (nextCost <= k) {
                        dp[i + 1][j][nextCost] = MAX(dp[i + 1][j][nextCost], dp[i][j][c] + grid[i + 1][j]);
                    }
                }
            }
        }
    }

    // Find the maximum score among all valid costs at the bottom-right cell
    int maxResult = -1;
    for (int c = 0; c <= k; c++) {
        maxResult = MAX(maxResult, dp[rows - 1][cols - 1][c]);
    }

    return maxResult;
}

int main() {
    int rows = 2;
    int cols = 2;
    int k = 1;

    // Mocking the 2D array structure used by LeetCode
    int row1[] = {0, 1};
    int row2[] = {2, 0};
    int* grid[] = {row1, row2};
    int gridColSize = 2;

    int result = maxPathScore(grid, rows, &gridColSize, k);

    printf("Input Grid:\n[0, 1]\n[2, 0]\nk = %d\n", k);
    printf("Maximum Path Score: %d\n", result);

    return 0;
}
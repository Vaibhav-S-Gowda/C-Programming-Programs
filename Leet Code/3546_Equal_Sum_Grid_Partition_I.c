#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canPartitionGrid(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];

    // Step 1: compute total sum
    long long total = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            total += grid[i][j];

    // Step 2: odd total → impossible
    if (total % 2 != 0) return false;

    long long half = total / 2;

    // Step 3: check horizontal cuts
    long long rowSum = 0;
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < n; j++)
            rowSum += grid[i][j];
        if (rowSum == half) return true;
    }

    // Step 4: check vertical cuts
    long long colSum = 0;
    for (int j = 0; j < n - 1; j++) {
        for (int i = 0; i < m; i++)
            colSum += grid[i][j];
        if (colSum == half) return true;
    }

    return false;
}

int main() {
    int m, n;

    printf("Enter number of rows: ");
    scanf("%d", &m);

    printf("Enter number of columns: ");
    scanf("%d", &n);

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

    // Column size array (as required by function signature)
    int* gridColSize = (int*)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        gridColSize[i] = n;
    }

    // Call function
    bool result = canPartitionGrid(grid, m, gridColSize);

    if (result)
        printf("Grid CAN be partitioned into two equal halves.\n");
    else
        printf("Grid CANNOT be partitioned into two equal halves.\n");

    // Free memory
    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }
    free(grid);
    free(gridColSize);

    return 0;
}
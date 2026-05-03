#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canPartitionGrid(int** grid, int gridSize, int* gridColSize) {
    unsigned long int sum = 0;

    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < *gridColSize; ++col) {
            sum += grid[row][col];
        }
    }

    // odd total → cannot split equally
    if (sum & 1) return false;

    // target half
    sum >>= 1;

    // horizontal cut
    unsigned long long half = 0;
    for (int row = 0; row < gridSize - 1; ++row) {
        for (int col = 0; col < *gridColSize; ++col) {
            half += grid[row][col];
        }
        if (half == sum) return true;
    }

    // vertical cut
    half = 0;
    for (int col = 0; col < (*gridColSize) - 1; ++col) {
        for (int row = 0; row < gridSize; ++row) {
            half += grid[row][col];
        }
        if (half == sum) return true;
    }

    return false;
}

int main() {
    int m, n;

    printf("Enter number of rows: ");
    scanf("%d", &m);

    printf("Enter number of columns: ");
    scanf("%d", &n);

    // allocate grid
    int** grid = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        grid[i] = (int*)malloc(n * sizeof(int));
    }

    // input grid
    printf("Enter grid values:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // column size array (as expected by function)
    int* gridColSize = (int*)malloc(sizeof(int));
    *gridColSize = n;

    // call function
    bool result = canPartitionGrid(grid, m, gridColSize);

    if (result)
        printf("Grid CAN be partitioned into two equal halves.\n");
    else
        printf("Grid CANNOT be partitioned into two equal halves.\n");

    // free memory
    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }
    free(grid);
    free(gridColSize);

    return 0;
}
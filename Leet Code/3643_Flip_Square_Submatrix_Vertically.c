#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 */
int** reverseSubmatrix(int** grid, int gridSize, int* gridColSize, int x, int y, int k, int* returnSize, int** returnColumnSizes) {
    // 1. Set the return metadata
    *returnSize = gridSize;
    *returnColumnSizes = (int*)malloc(gridSize * sizeof(int));
    
    // 2. Allocate the top-level pointers for the new matrix
    int** result = (int**)malloc(gridSize * sizeof(int*));

    for (int i = 0; i < gridSize; i++) {
        int cols = gridColSize[i];
        (*returnColumnSizes)[i] = cols;
        result[i] = (int*)malloc(cols * sizeof(int));
        
        for (int j = 0; j < cols; j++) {
            // Check if the current cell (i, j) is inside the k*k submatrix
            // starting at (x, y)
            if (i >= x && i < x + k && j >= y && j < y + k) {
                /* Vertical Flip Logic:
                   The local row index within the submatrix is (i - x).
                   The flipped local row index is (k - 1 - (i - x)).
                   The target global row is x + (k - 1 - (i - x)).
                */
                int targetRow = x + k - 1 - (i - x);
                result[i][j] = grid[targetRow][j];
            } else {
                // Otherwise, just copy the original value
                result[i][j] = grid[i][j];
            }
        }
    }

    return result;
}

int main() {
    int gridSize = 4;
    int colSizeValues[] = {4, 4, 4, 4};
    
    // Allocate and initialize input grid
    int** grid = (int**)malloc(gridSize * sizeof(int*));
    for (int i = 0; i < gridSize; i++) {
        grid[i] = (int*)malloc(colSizeValues[i] * sizeof(int));
        for (int j = 0; j < colSizeValues[i]; j++) {
            grid[i][j] = i * 4 + j + 1; // Fills 1 through 16
        }
    }

    printf("Original Grid:\n");
    printMatrix(grid, gridSize, colSizeValues);

    int returnSize;
    int* returnColumnSizes;
    
    // Reverse a 3x3 submatrix starting at row 0, col 1
    int** result = reverseSubmatrix(grid, gridSize, colSizeValues, 0, 1, 3, &returnSize, &returnColumnSizes);

    printf("\nFlipped Grid (3x3 at 0,1):\n");
    printMatrix(result, returnSize, returnColumnSizes);

    // Memory Cleanup
    for (int i = 0; i < gridSize; i++) {
        free(grid[i]);
        free(result[i]);
    }
    free(grid);
    free(result);
    free(returnColumnSizes);

    return 0;
}
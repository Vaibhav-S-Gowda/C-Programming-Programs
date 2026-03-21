#include <stdio.h>   // For printf
#include <stdlib.h>  // For malloc and free

/**
 * Function to reverse a k*k submatrix vertically
 */
int** reverseSubmatrix(int** grid, int gridSize, int* gridColSize, int x, int y, int k, int* returnSize, int** returnColumnSizes) {
    *returnSize = gridSize;
    *returnColumnSizes = (int*)malloc(gridSize * sizeof(int));
    int** result = (int**)malloc(gridSize * sizeof(int*));

    for (int i = 0; i < gridSize; i++) {
        int cols = gridColSize[i];
        (*returnColumnSizes)[i] = cols;
        result[i] = (int*)malloc(cols * sizeof(int));
        
        for (int j = 0; j < cols; j++) {
            if (i >= x && i < x + k && j >= y && j < y + k) {
                int sourceRow = x + k - 1 - (i - x);
                result[i][j] = grid[sourceRow][j];
            } else {
                result[i][j] = grid[i][j];
            }
        }
    }
    return result;
}

/**
 * Helper function to print the matrix.
 * It MUST be defined before main() if you don't use a prototype.
 */
void printMatrix(int** matrix, int rows, int* colSizes) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colSizes[i]; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int gridSize = 4;
    int colSizeValues[] = {4, 4, 4, 4};
    
    // Allocate and initialize input grid
    int** grid = (int**)malloc(gridSize * sizeof(int*));
    for (int i = 0; i < gridSize; i++) {
        grid[i] = (int*)malloc(colSizeValues[i] * sizeof(int));
        for (int j = 0; j < colSizeValues[i]; j++) {
            grid[i][j] = i * 4 + j + 1; 
        }
    }

    printf("Original Grid:\n");
    printMatrix(grid, gridSize, colSizeValues);

    int returnSize;
    int* returnColumnSizes;
    
    // Flip a 3x3 submatrix starting at row 0, col 1
    int** result = reverseSubmatrix(grid, gridSize, colSizeValues, 0, 1, 3, &returnSize, &returnColumnSizes);

    printf("\nFlipped Grid (3x3 at 0,1):\n");
    printMatrix(result, returnSize, returnColumnSizes);

    // Cleanup
    for (int i = 0; i < gridSize; i++) {
        free(grid[i]);
        free(result[i]);
    }
    free(grid);
    free(result);
    free(returnColumnSizes);

    return 0;
}
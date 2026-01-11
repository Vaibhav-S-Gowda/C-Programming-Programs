#include <stdio.h>
#include <stdlib.h>

void rotate(int** matrix, int matrixSize, int* matrixColSize) {

    // Step 1: Transpose
    for (int i = 0; i < matrixSize; i++) {
        for (int j = i + 1; j < matrixSize; j++) {
            matrix[i][j] = matrix[i][j] + matrix[j][i];
            matrix[j][i] = matrix[i][j] - matrix[j][i];
            matrix[i][j] = matrix[i][j] - matrix[j][i];
        }
    }

    // Step 2: Reverse each row
    for (int i = 0; i < matrixSize; i++) {
        int left = 0, right = matrixSize - 1;
        while (left < right) {
            int temp = matrix[i][left];
            matrix[i][left] = matrix[i][right];
            matrix[i][right] = temp;
            left++;
            right--;
        }
    }
}

int main() {
    int matrixSize = 3;
    int matrixColSize = 3;

    // Allocate matrix
    int** matrix = malloc(matrixSize * sizeof(int*));
    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = malloc(matrixColSize * sizeof(int));
    }

    // Initialize matrix
    int values[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (int i = 0; i < matrixSize; i++)
        for (int j = 0; j < matrixColSize; j++)
            matrix[i][j] = values[i][j];

    // Rotate matrix
    rotate(matrix, matrixSize, &matrixColSize);

    // Print result
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < matrixSize; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}


/* 
    int** matrix → dynamically allocated 2-D array

    matrixColSize is passed by pointer (LeetCode convention)

    Rotation is done in-place

    Logic = transpose + reverse rows

    Time complexity: O(n²)

    Space complexity: O(1) (in-place) 
*/
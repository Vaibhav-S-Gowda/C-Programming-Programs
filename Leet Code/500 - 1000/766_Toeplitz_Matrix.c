#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isToeplitzMatrix(int** matrix, int matrixSize, int* matrixColSize) {
    int rows = matrixSize;
    int cols = matrixColSize[0];

    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < cols; j++) {
            if (matrix[i][j] != matrix[i - 1][j - 1]) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    int rows = 3, cols = 4;

    int** matrix = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
    }

    int matrixColSize[] = {cols};  // FIX

    printf("Provide values (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    if (isToeplitzMatrix(matrix, rows, matrixColSize)) {
        printf("Matrix is Toeplitz\n");
    } else {
        printf("Matrix is Not Toeplitz\n");
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}


/*
    Why We Start From (1,1)
        (0,0) has no top-left neighbor
        Starting at (1,1) avoids going outside the matrix
        Every diagonal relationship is checked exactly once
*/

/*
    Tracing

        i=1, j=1
        matrix[1][1] == matrix[0][0]   ✓

        i=1, j=2
        matrix[1][2] == matrix[0][1]   ✓

        i=1, j=3
        matrix[1][3] == matrix[0][2]   ✓

        i=2, j=1
        matrix[2][1] == matrix[1][0]   ✓

        i=2, j=2
        matrix[2][2] == matrix[1][1]   ✓

        i=2, j=3
        matrix[2][3] == matrix[1][2]   ✓

*/
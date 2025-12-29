#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isToeplitzMatrix(int** matrix, int rows, int cols) {
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

    printf("Provide values (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    if (isToeplitzMatrix(matrix, rows, cols)) {
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

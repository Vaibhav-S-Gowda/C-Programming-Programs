#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// check if matrices are equal
bool isEqual(int** mat, int** target, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != target[i][j])
                return false;
        }
    }
    return true;
}

// rotate matrix 90° clockwise
void rotate(int** mat, int n) {
    // transpose
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }
    }

    // reverse each row
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            int temp = mat[i][j];
            mat[i][j] = mat[i][n - j - 1];
            mat[i][n - j - 1] = temp;
        }
    }
}

bool findRotation(int** mat, int matSize, int* matColSize,
                  int** target, int targetSize, int* targetColSize) {
    
    int n = matSize;

    for (int k = 0; k < 4; k++) {
        if (isEqual(mat, target, n))
            return true;
        rotate(mat, n);
    }

    return false;
}

int main() {
    int n = 3;

    // allocate mat
    int** mat = (int**)malloc(n * sizeof(int*));
    int** target = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        mat[i] = (int*)malloc(n * sizeof(int));
        target[i] = (int*)malloc(n * sizeof(int));
    }

    // initialize mat
    int tempMat[3][3] = {
        {0,1,0},
        {0,0,1},
        {1,1,1}
    };

    // initialize target
    int tempTarget[3][3] = {
        {1,0,0},
        {1,0,1},
        {1,1,0}
    };

    // copy values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = tempMat[i][j];
            target[i][j] = tempTarget[i][j];
        }
    }

    int matColSize[3] = {3,3,3};
    int targetColSize[3] = {3,3,3};

    if (findRotation(mat, n, matColSize, target, n, targetColSize))
        printf("true\n");
    else
        printf("false\n");

    // free memory
    for (int i = 0; i < n; i++) {
        free(mat[i]);
        free(target[i]);
    }
    free(mat);
    free(target);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** rotateTheBox(char** boxGrid, int boxGridSize, int* boxGridColSize,
                    int* returnSize, int** returnColumnSizes) {

    for (int i = 0; i < boxGridSize; i++) {
        int l_idx = 0;
        int r_idx = 1;
        bool stone_found = (boxGrid[i][l_idx] == '#') ? true : false;

        for (int j = 1; j < boxGridColSize[0]; j++) {

            if (!stone_found && (boxGrid[i][j] == '#')) {
                stone_found = true;
                l_idx = j;
            }

            if (stone_found) {

                if (l_idx == j) {
                    r_idx = l_idx + 1;
                    continue;
                }

                if (boxGrid[i][j] == '#') {
                    r_idx++;
                }
                else if (boxGrid[i][j] == '*') {
                    l_idx = j + 1;
                    r_idx = l_idx;
                    stone_found = false;
                }
                else {
                    boxGrid[i][l_idx++] = '.';
                    boxGrid[i][r_idx++] = '#';
                }
            }
        }
    }

    // Create rotated matrix
    char **ret = calloc(boxGridColSize[0], sizeof(char *));

    for (int i = 0; i < boxGridColSize[0]; i++) {
        ret[i] = calloc(boxGridSize, sizeof(char));
    }

    int *retColSizes = calloc(boxGridColSize[0], sizeof(int));

    for (int i = 0; i < boxGridColSize[0]; i++) {
        retColSizes[i] = boxGridSize;
    }

    // Rotate
    for (int i = 0; i < boxGridSize; i++) {
        for (int j = 0; j < boxGridColSize[0]; j++) {
            ret[j][boxGridSize - i - 1] = boxGrid[i][j];
        }
    }

    *returnSize = boxGridColSize[0];
    *returnColumnSizes = retColSizes;

    return ret;
}

int main() {

    int rows = 2;
    int cols = 4;

    char **boxGrid = malloc(rows * sizeof(char*));

    boxGrid[0] = malloc(cols * sizeof(char));
    boxGrid[1] = malloc(cols * sizeof(char));

    // Example:
    // # . * .
    // # # * .

    boxGrid[0][0] = '#';
    boxGrid[0][1] = '.';
    boxGrid[0][2] = '*';
    boxGrid[0][3] = '.';

    boxGrid[1][0] = '#';
    boxGrid[1][1] = '#';
    boxGrid[1][2] = '*';
    boxGrid[1][3] = '.';

    int boxGridColSize[2] = {4, 4};

    int returnSize;
    int *returnColumnSizes;

    char **result = rotateTheBox(
        boxGrid,
        rows,
        boxGridColSize,
        &returnSize,
        &returnColumnSizes
    );

    printf("Rotated Box:\n");

    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%c ", result[i][j]);
        }
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < rows; i++) {
        free(boxGrid[i]);
    }
    free(boxGrid);

    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }
    free(result);

    free(returnColumnSizes);

    return 0;
}
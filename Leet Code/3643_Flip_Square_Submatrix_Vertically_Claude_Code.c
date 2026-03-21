#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Highly optimized submatrix reversal.
 * Note: This version aliases untouched rows to save time/memory.
 */

int** reverseSubmatrix(int** grid, int gridSize, int* gridColSize,
                       int x, int y, int k,
                       int* returnSize, int** returnColumnSizes) {

    /* ── 1. Metadata: point returnColumnSizes straight at gridColSize ── */
    *returnSize = gridSize;
    *returnColumnSizes = gridColSize;   // no malloc/copy needed

    /* ── 2. Allocate result row-pointer array only ── */
    int** result = (int**)malloc(gridSize * sizeof(int*));

    /* ── 3. Rows OUTSIDE submatrix: alias, don't copy ── */
    for (int i = 0; i < x; i++)         result[i] = grid[i];
    for (int i = x + k; i < gridSize; i++) result[i] = grid[i];

    /* ── 4. Rows INSIDE submatrix: allocate only these k rows ── */
    for (int i = 0; i < k; i++) {
        int srcIdx = x + k - 1 - i;       // mirrored row index
        int dstIdx = x + i;
        int cols   = gridColSize[dstIdx];
        int* resRow = (int*)malloc(cols * sizeof(int));
        result[dstIdx] = resRow;

        int* origRow = grid[dstIdx];
        int* srcRow  = grid[srcIdx];

        // Part A: before submatrix
        if (y > 0)
            memcpy(resRow, origRow, y * sizeof(int));

        // Part B: the flip window — one memcpy, no loop
        memcpy(resRow + y, srcRow + y, k * sizeof(int));

        // Part C: after submatrix
        int tail = cols - y - k;
        if (tail > 0)
            memcpy(resRow + y + k, origRow + y + k, tail * sizeof(int));
    }

    return result;
}

int main() {
    int gridSize = 5;
    int colSizes[] = {5, 5, 5, 5, 5};
    
    // Allocate original grid
    int** grid = (int**)malloc(gridSize * sizeof(int*));
    for (int i = 0; i < gridSize; i++) {
        grid[i] = (int*)malloc(colSizes[i] * sizeof(int));
        for (int j = 0; j < colSizes[i]; j++) {
            grid[i][j] = (i + 1) * 10 + (j + 1); // e.g., 11, 12, 13...
        }
    }

    printf("Original Grid:\n");
    for(int i=0; i<gridSize; i++) {
        for(int j=0; j<colSizes[i]; j++) printf("%d ", grid[i][j]);
        printf("\n");
    }

    int returnSize;
    int* returnColSizes;
    // Flip 3x3 submatrix starting at row 1, col 1
    int x = 1, y = 1, k = 3;
    int** result = reverseSubmatrix(grid, gridSize, colSizes, x, y, k, &returnSize, &returnColSizes);

    printf("\nResult Grid (Flipped 3x3 at 1,1):\n");
    for(int i=0; i<returnSize; i++) {
        for(int j=0; j<returnColSizes[i]; j++) printf("%d ", result[i][j]);
        printf("\n");
    }

    /* ── Cleanup Logic ── */
    // Note: result[0] and result[4] point to the same memory as grid[0] and grid[4]
    // We only free the rows we actually malloced in the function (the flip zone)
    for (int i = x; i < x + k; i++) {
        free(result[i]);
    }
    free(result);
    free(returnColSizes);
    
    // Free the original grid
    for (int i = 0; i < gridSize; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}
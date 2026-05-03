#include <stdio.h>
#include <stdlib.h>

/* Comparator for qsort */
int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/* Backtracking with pruning */
void backtrack(
    int* candidates,
    int candidatesSize,
    int target,
    int start,
    int* path,
    int pathSize,
    int*** result,
    int* returnSize,
    int** returnColumnSizes,
    int* capacity
) {
    if (target == 0) {
        if (*returnSize >= *capacity) {
            *capacity *= 2;
            *result = realloc(*result, (*capacity) * sizeof(int*));
            *returnColumnSizes = realloc(*returnColumnSizes, (*capacity) * sizeof(int));
        }

        int* comb = malloc(pathSize * sizeof(int));
        for (int i = 0; i < pathSize; i++) {
            comb[i] = path[i];
        }

        (*result)[*returnSize] = comb;
        (*returnColumnSizes)[*returnSize] = pathSize;
        (*returnSize)++;
        return;
    }

    for (int i = start; i < candidatesSize; i++) {
        /* PRUNING */
        if (candidates[i] > target)
            break;

        path[pathSize] = candidates[i];
        backtrack(
            candidates,
            candidatesSize,
            target - candidates[i],
            i,                  // reuse allowed
            path,
            pathSize + 1,
            result,
            returnSize,
            returnColumnSizes,
            capacity
        );
    }
}

/*
 * Optimized API function
 */
int** combinationSum(
    int* candidates,
    int candidatesSize,
    int target,
    int* returnSize,
    int** returnColumnSizes
) {
    qsort(candidates, candidatesSize, sizeof(int), cmp);

    int capacity = 64;
    int** result = malloc(capacity * sizeof(int*));
    *returnColumnSizes = malloc(capacity * sizeof(int));

    *returnSize = 0;
    int* path = malloc(100 * sizeof(int));  // max depth

    backtrack(
        candidates,
        candidatesSize,
        target,
        0,
        path,
        0,
        &result,
        returnSize,
        returnColumnSizes,
        &capacity
    );

    free(path);
    return result;
}

/* ------------------- MAIN FUNCTION ------------------- */

int main() {
    int candidates[] = {2, 3, 6, 7};
    int candidatesSize = 4;
    int target = 7;

    int returnSize;
    int* returnColumnSizes;

    int** result = combinationSum(
        candidates,
        candidatesSize,
        target,
        &returnSize,
        &returnColumnSizes
    );

    printf("Optimized combinations:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d", result[i][j]);
            if (j + 1 < returnColumnSizes[i]) printf(", ");
        }
        printf("]\n");
        free(result[i]);
    }

    free(result);
    free(returnColumnSizes);

    return 0;
}

/*
    Step 1: Preprocessing (Sorting)
        Sort the array candidates in non-decreasing order

    Step 2: Initialize
        Create:
            An empty list result
            An empty list currentCombination

        Set returnSize = 0

    Step 3: Backtracking Function
        Define a recursive function:
            backtrack(startIndex, remainingTarget)
        Function Logic
            1. Base Case — Valid Combination
                If remainingTarget == 0:
                    Add a copy of currentCombination to result
                    Return
            2. Explore Candidates (with Pruning)
                For i from startIndex to n - 1:
                    1. Pruning Condition
                        If candidates[i] > remainingTarget:
                            Break the loop
                            (All subsequent elements are larger due to sorting)
                    2. Choose
                        Add candidates[i] to currentCombination
                    3. Recurse
                        Call
                            backtrack(i, remainingTarget − candidates[i])
                        (i is reused to allow unlimited usage)
                    4. Unchoose (Backtrack)
                        Remove last element from currentCombination

    Step 4: Initial Call
        Call
            backtrack(0, target)

    Step 5: Termination
        After recursion completes, result contains all valid combinations
        
*/
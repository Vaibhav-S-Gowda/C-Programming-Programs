#include <stdio.h>
#include <stdlib.h>

/* Helper function for backtracking */
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

        int* combination = malloc(pathSize * sizeof(int));
        for (int i = 0; i < pathSize; i++) {
            combination[i] = path[i];
        }

        (*result)[*returnSize] = combination;
        (*returnColumnSizes)[*returnSize] = pathSize;
        (*returnSize)++;
        return;
    }

    if (target < 0) return;

    for (int i = start; i < candidatesSize; i++) {
        path[pathSize] = candidates[i];
        backtrack(
            candidates,
            candidatesSize,
            target - candidates[i],
            i,                // reuse allowed
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
 * Main API function
 */
int** combinationSum(
    int* candidates,
    int candidatesSize,
    int target,
    int* returnSize,
    int** returnColumnSizes
) {
    int capacity = 100;
    int** result = malloc(capacity * sizeof(int*));
    *returnColumnSizes = malloc(capacity * sizeof(int));

    *returnSize = 0;
    int* path = malloc(100 * sizeof(int));  // max depth safeguard

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

    printf("Combinations:\n");
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
    Algorithm Steps

    1. Initialize result storage
        Create an empty list result
        Create an empty list columnSizes
        Initialize returnSize = 0

    2. Start backtracking
        Call recursive function backtrack with:
            start = 0
            currentSum = target
            currentPath = empty

    3. Recursive function: backtrack(start, currentSum, currentPath)
        * Base Case — Valid Combination
            If currentSum == 0:
                Store a copy of currentPath in result
                Record the length of currentPath in columnSizes
                Increment returnSize
                Return
        * Base Case — Invalid Path
            If currentSum < 0:
                Return immediately
        * Explore Choices
            For index i from start to n - 1:
                Append candidates[i] to currentPath
                Recursively call : backtrack(i, currentSum - candidates[i], currentPath)
                Remove last element from currentPath (backtrack)
    
    4. Termination
        Recursion completes when all possible paths are explored
        result contains all valid combinations
*/
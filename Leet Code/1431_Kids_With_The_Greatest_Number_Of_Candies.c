#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* kidsWithCandies(int* candies, int candiesSize, int extraCandies, int* returnSize) {
    *returnSize = candiesSize;
    bool* result = (bool*)malloc(candiesSize * sizeof(bool));
    
    if (result == NULL) return NULL;

    int maxCandies = 0;
    for (int i = 0; i < candiesSize; i++) {
        if (candies[i] > maxCandies) {
            maxCandies = candies[i];
        }
    }

    for (int i = 0; i < candiesSize; i++) {
        result[i] = (candies[i] + extraCandies >= maxCandies);
    }

    return result;
}

int main() {
    // Example Input
    int candies[] = {2, 3, 5, 1, 3};
    int candiesSize = 5;
    int extraCandies = 3;
    int returnSize; // This will be filled by the function

    // Call the function
    bool* result = kidsWithCandies(candies, candiesSize, extraCandies, &returnSize);

    // Print the results
    printf("Result: [");
    for (int i = 0; i < returnSize; i++) {
        printf("%s%s", result[i] ? "true" : "false", (i < returnSize - 1) ? ", " : "");
    }
    printf("]\n");

    // CRITICAL: Free the memory allocated by malloc
    free(result);

    return 0;
}
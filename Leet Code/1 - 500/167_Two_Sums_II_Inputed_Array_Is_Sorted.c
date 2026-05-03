#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int i = 0, j = numbersSize - 1;

    while (i < j) {
        if (numbers[i] + numbers[j] > target)
            j--;
        else if (numbers[i] + numbers[j] < target)
            i++;
        else {
            int* result = malloc(2 * sizeof(int));
            if (!result) {
                *returnSize = 0;
                return NULL;
            }
            result[0] = i + 1;  // 1-based index
            result[1] = j + 1;  // 1-based index
            *returnSize = 2;
            return result;
        }
    }
    *returnSize = 0;
    return NULL;
}

int main(void) {
    int numbers[] = {2, 7, 11, 15};
    int numbersSize = sizeof(numbers) / sizeof(numbers[0]);
    int target = 9;

    int returnSize = 0;
    int* result = twoSum(numbers, numbersSize, target, &returnSize);

    if (result != NULL && returnSize == 2) {
        printf("Indices: %d, %d\n", result[0], result[1]);
        free(result);  // mandatory to avoid memory leak
    } else {
        printf("No valid pair found.\n");
    }

    return 0;
}

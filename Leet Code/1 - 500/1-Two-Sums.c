#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int idx;
} Pair;

// Comparison function for qsort
int compare(const void *a, const void *b) {
    Pair *p1 = (Pair *)a;
    Pair *p2 = (Pair *)b;
    // Standard trick to avoid overflow in subtraction
    return (p1->val > p2->val) - (p1->val < p2->val);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    Pair *pairs = malloc(numsSize * sizeof(Pair));
    for (int i = 0; i < numsSize; i++) {
        pairs[i].val = nums[i];
        pairs[i].idx = i;
    }

    // Sort the pairs based on value
    qsort(pairs, numsSize, sizeof(Pair), compare);

    int left = 0;
    int right = numsSize - 1;
    int *result = NULL;

    while (left < right) {
        long sum = (long)pairs[left].val + pairs[right].val;
        if (sum == target) {
            result = malloc(2 * sizeof(int));
            result[0] = pairs[left].idx;
            result[1] = pairs[right].idx;
            *returnSize = 2;
            break; 
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    free(pairs);
    if (!result) *returnSize = 0;
    return result;
}

int main() {
    int nums[] = {3, 2, 4};
    int target = 6;
    int returnSize;
    
    int* result = twoSum(nums, 3, target, &returnSize);
    
    if (returnSize == 2) {
        printf("Indices: [%d, %d]\n", result[0], result[1]);
        free(result); // Don't forget to free the allocated result!
    } else {
        printf("No solution found.\n");
    }
    
    return 0;
}
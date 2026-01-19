#include <stdio.h>

int removeDuplicates(int* nums, int numsSize) {
    // If array is empty, no duplicates to remove
    if (numsSize == 0)
        return 0;

    int k = 1;  // Index for placing next unique element

    // Start from second element since first is always unique
    for (int i = 1; i < numsSize; i++) {
        // If current element is different from previous
        if (nums[i] != nums[i - 1]) {
            nums[k] = nums[i];  // Place unique element
            k++;                // Move to next position
        }
    }

    // k represents the number of unique elements
    return k;
}

int main() {
    int nums[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int newLength = removeDuplicates(nums, numsSize);

    printf("Number of unique elements: %d\n", newLength);
    printf("Array after removing duplicates: ");

    // Print only the unique portion of the array
    for (int i = 0; i < newLength; i++) {
        printf("%d ", nums[i]);
    }

    return 0;
}
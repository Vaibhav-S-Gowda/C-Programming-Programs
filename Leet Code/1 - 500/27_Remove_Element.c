#include <stdio.h>

int removeElement(int* nums, int numsSize, int val) {
    // If array is empty, nothing to remove
    if (numsSize == 0)
        return 0;

    int k = 0;  // Points to position for next valid element

    // Traverse the array
    for (int i = 0; i < numsSize; i++) {
        // Keep only elements that are not equal to val
        if (nums[i] != val) {
            nums[k] = nums[i];  // Overwrite unwanted elements
            k++;                // Move to next position
        }
    }

    // k represents the number of valid elements
    return k;
}

int main() {
    int nums[] = {3, 2, 2, 3};
    int val = 3;
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int newLength = removeElement(nums, numsSize, val);

    printf("New length: %d\n", newLength);
    printf("Array after removal: ");

    // Print only the valid part of the array
    for (int i = 0; i < newLength; i++) {
        printf("%d ", nums[i]);
    }

    return 0;
}

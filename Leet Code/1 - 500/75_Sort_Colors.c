#include <stdio.h>

void sortColors(int* nums, int numsSize) {
    int low = 0;
    int mid = 0;
    int high = numsSize - 1;
    int temp;

    while (mid <= high) {
        if (nums[mid] == 0) {
            // Swap nums[low] and nums[mid], then move both pointers
            temp = nums[low];
            nums[low] = nums[mid];
            nums[mid] = temp;
            low++;
            mid++;
        } 
        else if (nums[mid] == 1) {
            // White is in the correct middle spot, just move mid
            mid++;
        } 
        else { // nums[mid] == 2
            // Swap nums[mid] and nums[high], shrink high boundary
            temp = nums[mid];
            nums[mid] = nums[high];
            nums[high] = temp;
            high--;
        }
    }
}

int main() {
    // Example test case
    int nums[] = {2, 0, 2, 1, 1, 0};
    int n = sizeof(nums) / sizeof(nums[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", nums[i]);
    }

    sortColors(nums, n);

    printf("\nSorted array:   ");
    for (int i = 0; i < n; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}
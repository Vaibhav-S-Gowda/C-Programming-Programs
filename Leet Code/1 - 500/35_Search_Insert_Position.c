#include <stdio.h>

int searchInsert(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;

    // Standard binary search
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            return mid;                 // Target found
        } 
        else if (nums[mid] < target) {
            left = mid + 1;             // Search right half
        } 
        else {
            right = mid - 1;            // Search left half
        }
    }

    // Target not found; left is the correct insertion index
    return left;
}

int main() {
    int nums[] = {1, 3, 5, 6};
    int target = 2;

    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int index = searchInsert(nums, numsSize, target);
    printf("Insert position: %d\n", index);
    return 0;
}


/*
    Steps:
        mid = 1 → nums[1] = 3 > 2 → move right left
        mid = 0 → nums[0] = 1 < 2 → move left right
        loop ends

    Complexity Analysis
        Time Complexity: O(log n)
        Space Complexity: O(1)
*/
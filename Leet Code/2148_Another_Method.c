#include <stdio.h>
#include <limits.h>

int countElements(int* nums, int numsSize) {
    // If there are fewer than 3 elements, it's impossible to satisfy the condition
    if (numsSize < 3) return 0;

    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    int minCount = 0;
    int maxCount = 0;

    // Single pass to find min, max, and their frequencies
    for (int i = 0; i < numsSize; i++) {
        // Update Minimum
        if (nums[i] < minVal) {
            minVal = nums[i];
            minCount = 1;
        } else if (nums[i] == minVal) {
            minCount++;
        }

        // Update Maximum
        if (nums[i] > maxVal) {
            maxVal = nums[i];
            maxCount = 1;
        } else if (nums[i] == maxVal) {
            maxCount++;
        }
    }

    // If min and max are the same, all elements are identical; return 0
    if (minVal == maxVal) {
        return 0;
    }

    // The answer is the total elements minus those at the boundaries
    return numsSize - minCount - maxCount;
}

int main() {
    // Example 1
    int nums1[] = {11, 7, 2, 15};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("Example 1: %d\n", countElements(nums1, size1)); // Expected Output: 2

    // Example 2
    int nums2[] = {-3, 3, 3, 90};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("Example 2: %d\n", countElements(nums2, size2)); // Expected Output: 2

    // Example 3: All same elements
    int nums3[] = {5, 5, 5, 5};
    int size3 = sizeof(nums3) / sizeof(nums3[0]);
    printf("Example 3 (All same): %d\n", countElements(nums3, size3)); // Expected Output: 0

    return 0;
}

/*
    The Logic
        For an element to have both a strictly smaller and a strictly greater element in the same array, 
        it simply needs to exist somewhere in the "middle" of the range.
            - If an element is the minimum (min(nums)), 
                there is nothing strictly smaller than it.
            - If an element is the maximum (max(nums)), 
                there is nothing strictly greater than it.
        Therefore, any element $x$ satisfies the condition if:
            min(nums) < x < max(nums)
*/

/*
    Complexity Analysis
        Time Complexity: O(n). We traverse the array to find the min/max and then once more to count.
        Space Complexity: O(1). We only store a few integer variables regardless of the input size.
*/

#include <stdio.h>
#include <limits.h>

int countElements(int* nums, int numsSize) {
    if (numsSize < 3) return 0;

    int minVal = nums[0];
    int maxVal = nums[0];

    // Step 1: Find the absolute min and max in one pass
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < minVal) {
            minVal = nums[i];
        }
        if (nums[i] > maxVal) {
            maxVal = nums[i];
        }
    }

    int count = 0;
    // Step 2: Count elements that are strictly between min and max
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > minVal && nums[i] < maxVal) {
            count++;
        }
    }

    return count;
}

int main() {
    // Example array
    int nums[] = {-3, 3, 3, 90};

    // Calculate size of array
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    // Call function
    int result = countElements(nums, numsSize);

    // Print result
    printf("Count of elements strictly between min and max: %d\n", result);

    return 0;
}


/*
    Quick Trace: nums = [-3, 3, 3, 90]
        1. Min/Max Search: minVal becomes -3, maxVal becomes 90.
        2. Comparison:
           -> -3: Not strictly greater than -3 (Skip)
           -> 3: -3 < 3 < 90 is True (Count = 1)
           -> 3: -3 < 3 < 90 is True (Count = 2)
           -> 90: Not strictly smaller than 90 (Skip)
        3. Result: 2.
*/
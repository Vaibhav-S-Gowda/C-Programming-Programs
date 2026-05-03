#include <stdio.h>

int maxSubArray(const int* nums, int numsSize);

int main() {
    int nums[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int result = maxSubArray(nums, numsSize);

    printf("Maximum subarray sum: %d\n", result);

    return 0;
}

int maxSubArray(const int* nums, int numsSize) {
    int maxSum = nums[0];
    int currentSum = 0;

    for (int i = 0; i < numsSize; i++) {
        currentSum += nums[i];

        if (currentSum > maxSum) {
            maxSum = currentSum;
        }

        if (currentSum < 0) {
            currentSum = 0;
        }
    }
    return maxSum;
}

/*
    1. We walk through the array one number at a time.
    2. We keep adding numbers to a running sum.
    3. If the running sum becomes negative, we reset it to 0
        because a negative sum will only make future sums worse.
    4. Every time the running sum becomes bigger than what we have seen before,
        we save it as the answer.
    5. At the end, the saved value is the maximum subarray sum.

    This is called Kadane’s Algorithm.
*/
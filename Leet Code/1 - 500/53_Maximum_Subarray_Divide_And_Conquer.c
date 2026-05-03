#include <stdio.h>
#include <limits.h>

// Utility function to get maximum of three integers 
int max3(int a, int b, int c) {
    if (a >= b && a >= c)
        return a;
    else if (b >= a && b >= c)
        return b;
    else
        return c;
}

// Recursive divide and conquer function 
int maxSubArrayDC(int* nums, int left, int right) {
    /* Base case: single element */
    if (left == right)
        return nums[left];

    int mid = left + (right - left) / 2;

    /* Maximum subarray sum in left half */
    int leftMax = maxSubArrayDC(nums, left, mid);

    /* Maximum subarray sum in right half */
    int rightMax = maxSubArrayDC(nums, mid + 1, right);

    /* Maximum subarray sum crossing the mid */
    int sum = 0;
    int leftSum = INT_MIN;
    for (int i = mid; i >= left; i--) {
        sum += nums[i];
        if (sum > leftSum)
            leftSum = sum;
    }

    sum = 0;
    int rightSum = INT_MIN;
    for (int i = mid + 1; i <= right; i++) {
        sum += nums[i];
        if (sum > rightSum)
            rightSum = sum;
    }

    int crossSum = leftSum + rightSum;

    return max3(leftMax, rightMax, crossSum);
}

/* Wrapper function */
int maxSubArray(int* nums, int numsSize) {
    return maxSubArrayDC(nums, 0, numsSize - 1);
}

int main() {
    int nums[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int result = maxSubArray(nums, numsSize);
    printf("Maximum subarray sum: %d\n", result);

    return 0;
}

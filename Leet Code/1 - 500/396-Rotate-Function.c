#include <stdio.h>
#include <stdint.h>

int maxRotateFunction(int* nums, int numsSize) {
    // Use long long for intermediate sums to prevent 32-bit overflow
    long long current_f = 0;
    long long sum_nums = 0;
    long long n = numsSize;

    for (int i = 0; i < numsSize; i++) {
        sum_nums += nums[i];
        current_f += (long long)i * nums[i];
    }

    long long max_f = current_f;

    // Iteratively calculate F(k) based on F(k-1)
    // Formula: F(k) = F(k-1) + sum - n * nums[n-k]
    for (int k = 1; k < numsSize; k++) {
        current_f = current_f + sum_nums - n * nums[numsSize - k];

        if (current_f > max_f) {
            max_f = current_f;
        }
    }

    return (int)max_f;
}

int main() {
    // Example 1: nums = [4, 3, 2, 6]
    int nums1[] = {4, 3, 2, 6};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("Max Rotate Function (Ex 1): %d\n", maxRotateFunction(nums1, size1));

    // Example 2: nums = [100]
    int nums2[] = {100};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("Max Rotate Function (Ex 2): %d\n", maxRotateFunction(nums2, size2));

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int lengthOfLIS(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int* tails = (int*)malloc(numsSize * sizeof(int));
    int size = 0;

    for (int i = 0; i < numsSize; i++) {
        int left = 0, right = size;

        // binary search for the position
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (tails[mid] < nums[i])
                left = mid + 1;
            else
                right = mid;
        }

        tails[left] = nums[i];

        if (left == size)
            size++;
    }

    free(tails);
    return size;
}

int main() {
    int nums[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = sizeof(nums) / sizeof(nums[0]);

    int result = lengthOfLIS(nums, n);

    printf("Length of LIS: %d\n", result);  // Expected: 4

    return 0;
}
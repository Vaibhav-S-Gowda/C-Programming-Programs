#include <stdio.h>

int removeElement(int* nums, int numsSize, int val) {
    int left = 0;
    int right = numsSize - 1;

    while (left <= right) {
        if (nums[left] == val) {
            // Replace current element with the element at 'right'
            nums[left] = nums[right];
            right--;
        } else {
            left++;
        }
    }

    return left;
}

int main() {
    int nums[] = {3, 2, 2, 3, 4, 5, 5, 5, 8, 8};
    int val = 5;
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int newLength = removeElement(nums, numsSize, val);

    printf("New length: %d\n", newLength);
    printf("Array after removal: ");
    for (int i = 0; i < newLength; i++) {
        printf("%d ", nums[i]);
    }

    return 0;
}

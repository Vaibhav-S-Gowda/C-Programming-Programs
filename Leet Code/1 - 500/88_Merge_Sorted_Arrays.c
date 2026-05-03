#include <stdio.h>

// LeetCode 88 - Merge Sorted Array
void merge(int* nums1, int m, int* nums2, int n) {
    int i = m - 1;        // Last valid element in nums1
    int j = n - 1;        // Last element in nums2
    int k = m + n - 1;    // Last position in nums1

    // Merge from the end
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k--] = nums1[i--];
        } else {
            nums1[k--] = nums2[j--];
        }
    }

    // Copy remaining elements from nums2 if any
    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}

int main() {
    int nums1[] = {1, 2, 3, 0, 0, 0};
    int nums2[] = {2, 5, 6};

    int m = 3;  // number of valid elements in nums1
    int n = 3;  // number of elements in nums2

    merge(nums1, m, nums2, n);

    printf("Merged array: ");
    for (int i = 0; i < m + n; i++) {
        printf("%d ", nums1[i]);
    }

    return 0;
}

/*
    Compare 3 and 6 → write 6
    Compare 3 and 5 → write 5
    Compare 3 and 2 → write 3
    Compare 2 and 2 → write 2
    Copy remaining 1
*/
#include <stdio.h>
#include <math.h>

int maxDistance(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int i = 0; // Pointer for nums1
    int j = 0; // Pointer for nums2
    int max_dist = 0;

    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] <= nums2[j]) {
            int current_dist = j - i;
            if (current_dist > max_dist) {
                max_dist = current_dist;
            }
            j++;
        } else {
            i++;
            if (j < i) {
                j = i;
            }
        }
    }

    return max_dist;
}

int main() {
    int nums1[] = {55, 30, 5, 4, 2};
    int nums2[] = {100, 20, 10, 10, 5};
    
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    int size2 = sizeof(nums2) / sizeof(nums2[0]);

    int result = maxDistance(nums1, size1, nums2, size2);
    printf("Maximum Distance: %d\n", result);

    return 0;
}
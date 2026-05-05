#include <stdio.h>
#include <math.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    // 1. Always binary search on the smaller array for efficiency
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    int n1 = nums1Size;
    int n2 = nums2Size;
    int low = 0, high = n1;

    while (low <= high) {
        int cut1 = (low + high) / 2;
        int cut2 = (n1 + n2 + 1) / 2 - cut1;

        // 2. Determine boundary values, handling out-of-bounds with INF
        int l1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
        int l2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
        int r1 = (cut1 == n1) ? INT_MAX : nums1[cut1];
        int r2 = (cut2 == n2) ? INT_MAX : nums2[cut2];

        // 3. Check if we found the perfect partition
        if (l1 <= r2 && l2 <= r1) {
            if ((n1 + n2) % 2 == 0) {
                return (MAX(l1, l2) + MIN(r1, r2)) / 2.0;
            } else {
                return MAX(l1, l2);
            }
        } 
        // 4. Adjust binary search range
        else if (l1 > r2) {
            high = cut1 - 1;
        } else {
            low = cut1 + 1;
        }
    }
    return 0.0;
}

int main() {
    int nums1[] = {1, 3};
    int nums2[] = {2};
    int size1 = 2;
    int size2 = 1;

    double median = findMedianSortedArrays(nums1, size1, nums2, size2);
    
    printf("Array 1: [1, 3]\n");
    printf("Array 2: [2]\n");
    printf("The median is: %.2f\n", median);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * find an index i such that nums[i] == target and abs(i - start) is minimized.
 * Return abs(i - start).
 */
int getMinDistance(int* nums, int numsSize, int target, int start) {
    int distance = 0;
    
    // Expand outwards from the start index
    while (1) {
        // Check index to the right
        if (start + distance < numsSize && nums[start + distance] == target) {
            return distance;
        }
        // Check index to the left
        if (start - distance >= 0 && nums[start - distance] == target) {
            return distance;
        }
        
        distance++;
    }
}

int main() {
    // Example 1 from the problem description
    int nums[] = {1, 2, 3, 4, 5};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int target = 5;
    int start = 3;

    int result = getMinDistance(nums, numsSize, target, start);

    // Output results
    printf("Input Array: [");
    for(int i = 0; i < numsSize; i++) {
        printf("%d%s", nums[i], i == numsSize - 1 ? "" : ", ");
    }
    printf("]\n");
    printf("Target: %d, Start Index: %d\n", target, start);
    printf("Minimum Distance: %d\n", result);

    return 0;
}

// How it works:
// 1. Distance Variable: We start with distance = 0 (checking the start index itself).

// 2. Bidirectional Search: In each iteration of the while loop, we check two positions:
// -> start + distance (moving right)
// -> start - distance (moving left)

// 3. Boundary Guards: We use start + distance < numsSize and start - distance >= 0 to ensure we never look outside the bounds of the array.

// 4. Early Exit: Since the problem guarantees the target exists, the loop will always find a match and return the smallest possible distance immediately.
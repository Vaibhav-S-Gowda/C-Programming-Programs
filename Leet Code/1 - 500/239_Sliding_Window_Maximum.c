#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }

    int* result = (int*)malloc(sizeof(int) * (numsSize - k + 1));
    int* deque = (int*)malloc(sizeof(int) * numsSize); // Store indices
    int head = 0, tail = 0; // Deque pointers
    int resIdx = 0;

    for (int i = 0; i < numsSize; i++) {
        // 1. Remove indices that are out of the current window bound
        if (head < tail && deque[head] <= i - k) {
            head++;
        }

        // 2. Remove indices of elements smaller than the current element
        // (They can never be the maximum again)
        while (head < tail && nums[deque[tail - 1]] <= nums[i]) {
            tail--;
        }

        // 3. Add current index to deque
        deque[tail++] = i;

        // 4. If window has reached size k, the front of deque is the max
        if (i >= k - 1) {
            result[resIdx++] = nums[deque[head]];
        }
    }

    *returnSize = resIdx;
    free(deque);
    return result;
}

int main() {
    int nums[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 3;

    int returnSize;
    int* result = maxSlidingWindow(nums, numsSize, k, &returnSize);

    printf("Sliding window maximums:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free allocated memory
    free(result);

    return 0;
}


// Array:  [ 1,  3, -1, -3,  5 ]
// Window: [ 1,  3, -1 ]           -> Deque Front: [3]  (Max: 3)
//             [ 3, -1, -3 ]       -> Deque Front: [3]  (Max: 3)
//                 [ -1, -3, 5 ]   -> Deque Front: [5]  (Max: 5)

// ASCII BEHIND THE SEENS:

//        +-------+
// Input: | 1 | 3 | -1 | -3 | 5 |
//        +-------+

// i=2: [ 1, 3, -1 ]
//      Deque: | 3 | -1 |  <-- 3 is at the head.
//      Result: [3]

// i=3: [ 3, -1, -3 ]
//      Deque: | 3 | -1 | -3 | 
//      Result: [3, 3]

// i=4: [ -1, -3, 5 ]
//      Index 1 (value 3) is kicked out because it's out of range.
//      Values -1 and -3 are kicked out because 5 is "stronger."
//      Deque: | 5 |
//      Result: [3, 3, 5]
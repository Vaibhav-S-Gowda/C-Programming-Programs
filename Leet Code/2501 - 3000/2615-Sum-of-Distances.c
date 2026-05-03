#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct {
    int val;
    int idx;
} Node;

// Comparison function for sorting by value, then by index
int compare(const void* a, const void* b) {
    Node* nodeA = (Node*)a;
    Node* nodeB = (Node*)b;
    if (nodeA->val != nodeB->val) {
        return (nodeA->val > nodeB->val) - (nodeA->val < nodeB->val);
    }
    return nodeA->idx - nodeB->idx;
}

long long* distance(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    long long* arr = (long long*)malloc(sizeof(long long) * numsSize);
    Node* nodes = (Node*)malloc(sizeof(Node) * numsSize);

    for (int i = 0; i < numsSize; i++) {
        nodes[i].val = nums[i];
        nodes[i].idx = i;
    }

    // Sort nodes to group identical values together: O(n log n)
    qsort(nodes, numsSize, sizeof(Node), compare);

    int i = 0;
    while (i < numsSize) {
        int j = i;
        long long total_sum = 0;
        
        // Find the range [i, j) where all values are identical
        while (j < numsSize && nodes[j].val == nodes[i].val) {
            total_sum += nodes[j].idx;
            j++;
        }

        int count = j - i;
        long long prefix_sum = 0;
        
        // Calculate distances for this specific group in O(count)
        for (int k = 0; k < count; k++) {
            int current_idx = nodes[i + k].idx;
            
            // Math: Sum of left distances + Sum of right distances
            long long left_part = (long long)k * current_idx - prefix_sum;
            long long right_sum = total_sum - prefix_sum - current_idx;
            long long right_part = right_sum - (long long)(count - 1 - k) * current_idx;
            
            arr[current_idx] = left_part + right_part;
            prefix_sum += current_idx;
        }
        
        i = j; 
    }

    free(nodes);
    return arr;
}

int main() {
    // Example test case: [1, 3, 1, 1, 2]
    int nums[] = {1, 3, 1, 1, 2};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;

    long long* result = distance(nums, numsSize, &returnSize);

    // Print the result
    printf("Input:  [");
    for (int i = 0; i < numsSize; i++) printf("%d%s", nums[i], i == numsSize - 1 ? "" : ", ");
    printf("]\n");

    printf("Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("%lld%s", result[i], i == returnSize - 1 ? "" : ", ");
    }
    printf("]\n");

    // Clean up
    free(result);

    return 0;
}
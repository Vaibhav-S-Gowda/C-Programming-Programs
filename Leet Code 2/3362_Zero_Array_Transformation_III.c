#include <stdio.h>
#include <stdlib.h>

// Comparison function to sort queries by start index
int compareQueries(const void* a, const void* b) {
    int* q1 = *(int**)a;
    int* q2 = *(int**)b;
    return q1[0] - q2[0];
}

// Simple Max-Heap Structure
typedef struct {
    int* data;
    int size;
} MaxHeap;

void push(MaxHeap* hp, int val) {
    int i = hp->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (hp->data[p] >= val) break;
        hp->data[i] = hp->data[p];
        i = p;
    }
    hp->data[i] = val;
}

int pop(MaxHeap* hp) {
    int res = hp->data[0];
    int val = hp->data[--hp->size];
    int i = 0;
    while (i * 2 + 1 < hp->size) {
        int a = i * 2 + 1, b = i * 2 + 2;
        if (b < hp->size && hp->data[b] > hp->data[a]) a = b;
        if (hp->data[a] <= val) break;
        hp->data[i] = hp->data[a];
        i = a;
    }
    hp->data[i] = val;
    return res;
}

int maxRemoval(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    // 1. Sort queries by start index
    qsort(queries, queriesSize, sizeof(int*), compareQueries);

    // 2. Setup Priority Queue and Difference Array
    MaxHeap hp;
    hp.data = (int*)malloc(sizeof(int) * queriesSize);
    hp.size = 0;
    
    int* diff = (int*)calloc(numsSize + 1, sizeof(int));
    int current_decrement = 0;
    int used_queries = 0;
    int query_idx = 0;

    for (int i = 0; i < numsSize; i++) {
        // Apply difference array updates to get current coverage at index i
        current_decrement += diff[i];

        // Add all queries starting at the current index to the Max-Heap
        while (query_idx < queriesSize && queries[query_idx][0] == i) {
            push(&hp, queries[query_idx][1]);
            query_idx++;
        }

        // While nums[i] is still positive, we must pick the best available queries
        while (nums[i] > current_decrement) {
            if (hp.size == 0 || hp.data[0] < i) {
                free(hp.data);
                free(diff);
                return -1; // Impossible to reduce nums[i] to 0
            }
            
            // Greedy: Pick query with the furthest right endpoint
            int r = pop(&hp);
            current_decrement++;
            used_queries++;
            
            // Mark the end of this query's influence in the difference array
            if (r + 1 < numsSize) {
                diff[r + 1]--;
            }
        }
    }

    free(hp.data);
    free(diff);
    return queriesSize - used_queries;
}

int main() {
    int nums1[] = {2, 0, 2};
    int n1 = 3;
    int q1_0[] = {0, 2}, q1_1[] = {0, 2}, q1_2[] = {1, 1};
    int* queries1[] = {q1_0, q1_1, q1_2};
    int queriesSize1 = 3;
    int queriesColSize1[] = {2, 2, 2};

    // Corrected the function name from maxRemoved to maxRemoval
    int result1 = maxRemoval(nums1, n1, queries1, queriesSize1, queriesColSize1);
    printf("Example 1 Result: %d (Expected: 1)\n", result1);
}
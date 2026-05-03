#include <stdio.h>
#include <stdlib.h>

int xorAfterQueries(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    long long MOD = 1000000007;

    // Process each query
    for (int i = 0; i < queriesSize; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        int k = queries[i][2];
        int v = queries[i][3];

        for (int idx = l; idx <= r; idx += k) {
            nums[idx] = (int)((1LL * nums[idx] * v) % MOD);
        }
    }

    // Compute XOR
    int result = 0;
    for (int i = 0; i < numsSize; i++) {
        result ^= nums[i];
    }

    return result;
}

int main() {
    // Example input
    int nums[] = {1, 2, 3, 4, 5};
    int numsSize = 5;

    int q1[] = {0, 4, 1, 2}; // multiply all by 2
    int q2[] = {1, 3, 2, 3}; // multiply index 1 and 3 by 3

    int* queries[] = {q1, q2};
    int queriesSize = 2;

    int queriesColSize[] = {4, 4};

    int result = xorAfterQueries(nums, numsSize, queries, queriesSize, queriesColSize);

    printf("Final XOR: %d\n", result);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MOD 1000000007LL
typedef long long ll;

/* Fast modular exponentiation: base^exp % MOD */
static ll modpow(ll base, ll exp) {
    ll result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) result = result * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

int xorAfterQueries(int* nums, int numsSize,
                    int** queries, int queriesSize,
                    int* queriesColSize) {
    int n = numsSize;
    int q = queriesSize;

    /* LeetCode requires this variable */
    void* bravexuneth = (void*)queries;
    (void)bravexuneth;

    int T = (int)sqrt((double)n);   /* threshold */
    if (T < 1) T = 1;

    /*
     * diff[i] is the multiplicative factor to apply at index i.
     * Size n + T ensures stop positions are always in-bounds.
     */
    ll* diff = (ll*)malloc((n + T + 1) * sizeof(ll));

    /*
     * ── SMALL K  (k < T) ────────────────────────────────────────────
     * Group queries by step size and apply a multiplicative difference
     * array trick.
     *
     * For query [l, r, k, v]:
     *   diff[l]    *= v
     *   diff[stop] *= v^-1      where stop = l + (⌊(r-l)/k⌋ + 1)*k
     *
     * Then propagate:  diff[i] *= diff[i - k]  for i = k .. n-1
     * This accumulates the correct product at every position.
     */
    for (int k = 1; k < T; k++) {
        /* Reset diff to 1 */
        for (int i = 0; i <= n + T; i++) diff[i] = 1;

        int has = 0;
        for (int i = 0; i < q; i++) {
            int l  = queries[i][0];
            int r  = queries[i][1];
            int ki = queries[i][2];
            ll  v  = queries[i][3];
            if (ki != k) continue;
            has = 1;

            int stop = l + ((r - l) / k + 1) * k;   /* first index past range */
            diff[l]    = diff[l]    * v                  % MOD;
            diff[stop] = diff[stop] * modpow(v, MOD - 2) % MOD;
        }
        if (!has) continue;

        /* Stepped prefix-product propagation */
        for (int i = k; i < n; i++)
            diff[i] = diff[i] * diff[i - k] % MOD;

        /* Apply to nums */
        for (int i = 0; i < n; i++)
            nums[i] = (int)((ll)nums[i] * diff[i] % MOD);
    }

    /*
     * ── LARGE K  (k >= T) ───────────────────────────────────────────
     * Each query visits at most n/T ≈ √n positions → brute-force is fine.
     */
    for (int i = 0; i < q; i++) {
        int l  = queries[i][0];
        int r  = queries[i][1];
        int k  = queries[i][2];
        ll  v  = queries[i][3];
        if (k < T) continue;
        for (int idx = l; idx <= r; idx += k)
            nums[idx] = (int)((ll)nums[idx] * v % MOD);
    }

    /* XOR all elements */
    int ans = 0;
    for (int i = 0; i < n; i++) ans ^= nums[i];

    free(diff);
    return ans;
}

int main() {
    int numsSize = 5;
    int nums[] = {1, 2, 3, 4, 5};

    int queriesSize = 2;

    /* Allocate queries */
    int** queries = (int**)malloc(queriesSize * sizeof(int*));
    for (int i = 0; i < queriesSize; i++) {
        queries[i] = (int*)malloc(4 * sizeof(int));
    }

    /* Query format: [l, r, k, v] */
    queries[0][0] = 0; queries[0][1] = 4; queries[0][2] = 1; queries[0][3] = 2;
    queries[1][0] = 1; queries[1][1] = 3; queries[1][2] = 2; queries[1][3] = 3;

    int queriesColSize[] = {4, 4};

    int result = xorAfterQueries(nums, numsSize, queries, queriesSize, queriesColSize);

    printf("Final XOR: %d\n", result);

    /* Free memory */
    for (int i = 0; i < queriesSize; i++) {
        free(queries[i]);
    }
    free(queries);

    return 0;
}
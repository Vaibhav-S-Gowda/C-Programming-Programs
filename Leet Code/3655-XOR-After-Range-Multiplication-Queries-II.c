#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MOD 1000000007LL
typedef long long ll;

/*
 * MODULAR EXPONENTIATION  (Fast Power)
 *
 *  Goal: compute base^exp % MOD in O(log exp) steps
 *
 *  Example: 3^13, exp in binary = 1101
 *
 *  bit:    1    1    0    1
 *          |    |    |    |
 *  base:   3    9   81  6561
 *          ^2   ^2   ^2
 *
 *  result: 3  * 9  * -- * 6561  =  177147
 *  (only multiply result when bit = 1)
 *
 *  Used to compute modular inverse via Fermat's Little Theorem:
 *    v^(-1) ≡ v^(MOD-2)  mod MOD    (MOD is prime)
 *
 *  This lets us "undo" a multiplication under modular arithmetic,
 *  which is needed to cancel range-end markers in the diff array.
 */
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

/*
 * ═══════════════════════════════════════════════════════════════
 *  OVERALL STRATEGY  —  Square Root Decomposition
 * ═══════════════════════════════════════════════════════════════
 *
 *  Each query [l, r, k, v] multiplies:
 *    nums[l], nums[l+k], nums[l+2k], ...  (all indices <= r)
 *
 *  Brute force = O(n/k) per query, total O(nq) = 10^10  TOO SLOW
 *
 *  Key insight:  cost of a query depends on step size k
 *
 *    Large k  →  few positions touched   →  fast per query
 *    Small k  →  many positions touched  →  slow per query
 *
 *  Split at threshold T = floor(sqrt(n)):
 *
 *    k >= T  (LARGE):  at most n/T ≈ √n positions per query
 *                      ↳  brute force is fine
 *
 *    k <  T  (SMALL):  batch all queries of same k together
 *                      ↳  use a multiplicative diff array
 *
 *  Total time:
 *    Large k:  q × √n  ops
 *    Small k:  T × n   ops  (one sweep of length n per small k)
 *    Both ≈ O(n√n)  ≈  3×10^7 for n=10^5   ✓ fast enough
 *
 * ═══════════════════════════════════════════════════════════════
 */
int xorAfterQueries(int* nums, int numsSize,
                    int** queries, int queriesSize,
                    int* queriesColSize) {
    int n = numsSize;
    int q = queriesSize;
    void* bravexuneth = (void*)queries; /* required by problem */
    (void)bravexuneth;

    int T = (int)sqrt((double)n);
    if (T < 1) T = 1;

    /*
     *  diff[i] = pending multiplicative factor at index i
     *  Size n+T avoids bounds-check when writing stop markers
     *  past the end of the array.
     *
     *    diff[0]  diff[1]  diff[2]  ...  diff[n-1] | diff[n] .. diff[n+T-1]
     *    ─────────────────────────────────────────────────────────────────
     *    (all start at 1 = identity for multiplication)
     */
    ll* diff = (ll*)malloc((n + T + 1) * sizeof(ll));

    /* ─────────────────────────────────────────────────────────────
     *  PHASE 1 — SMALL K  (k from 1 up to T-1)
     * ─────────────────────────────────────────────────────────────
     *
     *  For each fixed step k, we process all same-k queries at once.
     *
     *  DIFF ARRAY TRICK (multiplicative version of range update):
     *
     *  Query [l=2, r=8, k=2, v=3]  touches indices: 2, 4, 6, 8
     *
     *  Naïve:
     *    nums[2] *= 3,  nums[4] *= 3,  nums[6] *= 3,  nums[8] *= 3
     *
     *  Instead, mark the diff array:
     *    diff[2]  *= 3          ← start multiplying here
     *    diff[10] *= 3^(-1)     ← stop (first position AFTER range)
     *                              stop = last + k = 8 + 2 = 10
     *
     *  Then run a prefix-product sweep with stride k:
     *    diff[i] *= diff[i - k]   for i = k, k+1, ..., n-1
     *
     *  This propagates the factor through the right positions only.
     *
     *  VISUAL (k=2, range [2..8]):
     *
     *  Index:  0    1    2    3    4    5    6    7    8    9   10
     *          |    |    |    |    |    |    |    |    |    |    |
     *  After
     *  marking: 1    1    3    1    1    1    1    1    1    1   3^-1
     *
     *  Sweep (i += k=2, two independent chains):
     *   Chain residue-0:  i=0,2,4,6,8,10,...
     *     running: 1 → 1*3=3 → 3*1=3 → 3*1=3 → 3*1=3 → 3*3^-1=1
     *   Chain residue-1:  i=1,3,5,7,9,...
     *     running: 1 → 1*1=1 → 1*1=1 → 1*1=1 → 1*1=1
     *
     *  Final diff:
     *  Index:  0    1    2    3    4    5    6    7    8    9   10
     *          |    |    |    |    |    |    |    |    |    |    |
     *          1    1    3    1    3    1    3    1    3    1    1
     *                    ↑         ↑         ↑         ↑
     *               exactly the indices touched by the query ✓
     *
     *  Multiple queries with same k just accumulate in the diff:
     *
     *  Query A: [2, 8, 2, 3]  →  diff[2]*=3,  diff[10]*=3^-1
     *  Query B: [4, 6, 2, 5]  →  diff[4]*=5,  diff[8] *=5^-1
     *
     *  After both:
     *  Index:  0    1    2    3    4    5    6    7    8    9   10
     *          1    1    3    1    5    1    1    1   5^-1  1  3^-1
     *
     *  After sweep (residue-0 chain only):
     *    i=0: run=1
     *    i=2: run=1*3=3
     *    i=4: run=3*5=15       ← both v=3 and v=5 active
     *    i=6: run=15*1=15
     *    i=8: run=15*5^-1=3    ← v=5 cancelled, v=3 still active
     *    i=10: run=3*3^-1=1    ← v=3 cancelled
     *
     *  nums[2]*=3, nums[4]*=15, nums[6]*=15, nums[8]*=3  ✓
     */
    for (int k = 1; k < T; k++) {
        /* Reset diff to identity (all 1s) */
        for (int i = 0; i <= n + T; i++) diff[i] = 1;

        int has = 0;
        for (int i = 0; i < q; i++) {
            int l  = queries[i][0];
            int r  = queries[i][1];
            int ki = queries[i][2];
            ll  v  = queries[i][3];
            if (ki != k) continue;
            has = 1;

            /*
             *  Compute stop = last-touched-index + k
             *
             *  last = l + floor((r - l) / k) * k
             *  stop = last + k
             *       = l + (floor((r-l)/k) + 1) * k
             *
             *  Example: l=1, r=6, k=2
             *    visited = 1, 3, 5   (NOT 7, that exceeds r)
             *    last = 1 + floor(5/2)*2 = 1 + 4 = 5
             *    stop = 5 + 2 = 7
             *
             *  Note: stop % k == l % k, so it falls on the same
             *  residue chain and will be visited during the sweep.
             */
            int stop = l + ((r - l) / k + 1) * k;
            diff[l]    = diff[l]    * v                  % MOD;
            diff[stop] = diff[stop] * modpow(v, MOD - 2) % MOD;
        }
        if (!has) continue;

        /*
         *  STEPPED PREFIX-PRODUCT PROPAGATION
         *
         *  diff[i] *= diff[i - k]    for i = k .. n-1
         *
         *  The loop visits ALL indices 0..n-1, but the multiplication
         *  only connects positions that share the same residue mod k.
         *
         *  i=k:   diff[k]   *= diff[0]      (residue 0)
         *  i=k+1: diff[k+1] *= diff[1]      (residue 1)
         *  ...
         *  i=2k:  diff[2k]  *= diff[k]      (residue 0, uses updated diff[k])
         *  i=2k+1:diff[2k+1]*= diff[k+1]   (residue 1, uses updated diff[k+1])
         *
         *  Each residue class is propagated independently. ✓
         *
         *  After propagation, diff[i] holds the total multiplier
         *  that must be applied to nums[i].
         */
        for (int i = k; i < n; i++)
            diff[i] = diff[i] * diff[i - k] % MOD;

        for (int i = 0; i < n; i++)
            nums[i] = (int)((ll)nums[i] * diff[i] % MOD);
    }

    /* ─────────────────────────────────────────────────────────────
     *  PHASE 2 — LARGE K  (k >= T)
     * ─────────────────────────────────────────────────────────────
     *
     *  With k >= T = √n, each query visits at most n/k <= √n positions.
     *
     *  Example: n=100, T=10, k=20, query [l=3, r=83]:
     *
     *    Visited:  3   23   43   63   83
     *              |    |    |    |    |
     *              └────┴────┴────┴────┘   only 5 positions  (≤ √100 = 10) ✓
     *
     *  Direct multiplication is O(√n) per query = safe to brute-force.
     *
     *  Total cost for all large-k queries: q × √n = 10^5 × 316 ≈ 3×10^7 ✓
     */
    for (int i = 0; i < q; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        int k = queries[i][2];
        ll  v = queries[i][3];
        if (k < T) continue;                    /* already handled above */
        for (int idx = l; idx <= r; idx += k)
            nums[idx] = (int)((ll)nums[idx] * v % MOD);
    }

    /* ─────────────────────────────────────────────────────────────
     *  PHASE 3 — XOR reduction
     *
     *  XOR all elements:  ans = nums[0] ^ nums[1] ^ ... ^ nums[n-1]
     *
     *   4 ^ 18 ^ 2 ^ 15 ^ 4
     *   = 0b00100  (4)
     *   ^ 0b10010  (18)
     *   = 0b10110  (22)
     *   ^ 0b00010  (2)
     *   = 0b10100  (20)
     *   ^ 0b01111  (15)
     *   = 0b11011  (27)
     *   ^ 0b00100  (4)
     *   = 0b11111  (31) ✓
     * ─────────────────────────────────────────────────────────────
     */
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
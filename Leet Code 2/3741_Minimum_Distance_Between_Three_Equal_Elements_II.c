/*
 * LeetCode 3741 — Minimum Distance Between Three Equal Elements II
 *
 * DISTANCE DEFINITION:
 *   For triplet (i < j < k) where nums[i] == nums[j] == nums[k]:
 *   dist = (j-i) + (k-j) + (k-i)
 *        = 2*(k-i)         ← simplifies to double the span
 *
 * BUG FIX:
 *   Old: d = idxs[t+2] - idxs[t]        ← only span, gives 3
 *   New: d = 2*(idxs[t+2] - idxs[t])    ← sum of all pairs, gives 6
 *
 * WHY CONSECUTIVE TRIPLETS STILL WORK:
 *   If indices = [a, b, c, d, ...], then 2*(c-a) <= 2*(d-a)
 *   Minimizing span also minimizes 2*span — window stays O(n).
 *
 * UNDER THE HOOD — example: nums = [1,2,1,1,3]
 *
 *  idx:    0   1   2   3   4
 *  val:   [1]  2  [1] [1]  3
 *          |       |   |
 *          └───────┴───┘
 *        (j-i)=2  (k-j)=1  (k-i)=3
 *         sum = 2+1+3 = 6  ✓
 *
 * HASH MAP STATE after pass 1:
 *  key=1 → [0, 2, 3]   ← 3 hits, eligible
 *  key=2 → [1]          ← 1 hit,  skip
 *  key=3 → [4]          ← 1 hit,  skip
 *
 * TRIPLET WINDOW for key=1:
 *  t=0: idxs[0]=0, idxs[1]=2, idxs[2]=3
 *       d = 2*(3-0) = 6   ← only triplet, so ans = 6
 *
 * COMPLEXITY:
 *  Time:  O(n)  — each index touches hash map once in pass 1,
 *                  pass 2 visits each index at most once total
 *  Space: O(n)  — n (value, index) pairs stored across all nodes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HT_CAP 1024           /* power-of-2 → replace % with &  */
#define MASK   (HT_CAP - 1)

typedef struct Node {
    int  key;                 /* value in nums[]                 */
    int *idxs;                /* sorted list of indices (free!)  */
    int  cnt, cap;
    struct Node *next;        /* chaining for hash collisions    */
} Node;

static Node *ht[HT_CAP];     /* static → zeroed at program load */

/*
 * FNV-1a hash — fast, good distribution, no division
 *   h ^= byte, then h *= large prime
 *   final & MASK replaces expensive modulo
 */
static int hash(int k) {
    unsigned int h = 2166136261u;
    h ^= (unsigned char)k;
    h *= 16777619u;
    return (int)(h & MASK);
}

/*
 * push(k, i) — append index i under value k
 *   First call for k: allocate Node + small idxs buffer (cap=4)
 *   Subsequent calls:  just append (realloc doubles if full)
 *   Indices arrive in order 0..n-1 → idxs[] is always sorted
 */
static void push(int k, int i) {
    int h = hash(k);
    Node *n = ht[h];
    while (n && n->key != k) n = n->next;
    if (!n) {
        n        = calloc(1, sizeof(*n));
        n->key   = k;
        n->cap   = 4;
        n->idxs  = malloc(n->cap * sizeof(int));
        n->next  = ht[h];
        ht[h]    = n;
    }
    if (n->cnt == n->cap) {           /* grow buffer × 2         */
        n->cap  *= 2;
        n->idxs  = realloc(n->idxs, n->cap * sizeof(int));
    }
    n->idxs[n->cnt++] = i;
}

int minimumDistance(int *nums, int n) {
    memset(ht, 0, sizeof(ht));

    /* ── PASS 1: group indices by value ── O(n) ── */
    for (int i = 0; i < n; i++) push(nums[i], i);

    int ans = -1;

    /* ── PASS 2: slide size-3 window per value ── O(n) total ── */
    for (int b = 0; b < HT_CAP; b++) {
        for (Node *nd = ht[b]; nd; nd = nd->next) {
            if (nd->cnt < 3) continue;   /* need >= 3 occurrences */
            for (int t = 0; t + 2 < nd->cnt; t++) {
                /*
                 * FIX: distance = sum of all three pairwise gaps
                 *   (j-i) + (k-j) + (k-i)  =  2*(k-i)
                 *   OLD line was: d = nd->idxs[t+2] - nd->idxs[t]
                 */
                int d = 2 * (nd->idxs[t+2] - nd->idxs[t]);   /* ← FIX */
                if (ans < 0 || d < ans) ans = d;
            }
        }
    }

    /* ── PASS 3: free all heap memory ── */
    for (int b = 0; b < HT_CAP; b++) {
        for (Node *nd = ht[b], *nx; nd; nd = nx) {
            nx = nd->next;
            free(nd->idxs);
            free(nd);
        }
        ht[b] = NULL;
    }
    return ans;                          /* -1 if no triplet found */
}

/* ── quick test driver ── */
int main(void) {
    int a[] = {1,2,1,1,3};
    int n    = sizeof(a)/sizeof(a[0]);
    printf("ans = %d\n", minimumDistance(a, n));   /* expect 6 */

    int b[] = {1,2,3,2,1,3,2};
    n = sizeof(b)/sizeof(b[0]);
    printf("ans = %d\n", minimumDistance(b, n));   /* 2*(6-1)=10 */

    int c[] = {1,2,3};
    n = sizeof(c)/sizeof(c[0]);
    printf("ans = %d\n", minimumDistance(c, n));   /* -1 */
    return 0;
}

//         old formula counted only ONE gap (span)
//         new formula counts ALL THREE pairwise gaps

//   i         j     k
//   ●─────────●─────●
//   └──(j-i)──┘     │     } these three = 2*(k-i)
//   └────(k-i)──────┘     }
//             └(k-j)┘     }
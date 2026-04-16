#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int idx;
} Node;

int compareNodes(const void* a, const void* b) {
    Node* n1 = (Node*)a;
    Node* n2 = (Node*)b;
    if (n1->val != n2->val) return n1->val - n2->val;
    return n1->idx - n2->idx;
}

int* solveQueries(int* nums, int numsSize, int* queries, int queriesSize, int* returnSize) {
    int n = numsSize;
    Node* nodes = (Node*)malloc(n * sizeof(Node));
    for (int i = 0; i < n; i++) {
        nodes[i].val = nums[i];
        nodes[i].idx = i;
    }

    qsort(nodes, n, sizeof(Node), compareNodes);

    int* pos_in_sorted = (int*)malloc(n * sizeof(int));
    int* group_start   = (int*)malloc(n * sizeof(int));
    int* group_count   = (int*)malloc(n * sizeof(int));

    int current = 0;
    while (current < n) {
        int start = current;
        while (current < n && nodes[current].val == nodes[start].val) {
            pos_in_sorted[nodes[current].idx] = current;
            current++;
        }
        int count = current - start;
        for (int i = start; i < current; i++) {
            group_start[i] = start;
            group_count[i] = count;
        }
    }

    int* result = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;

    for (int i = 0; i < queriesSize; i++) {
        int q_idx      = queries[i];
        int sorted_pos = pos_in_sorted[q_idx];
        int start      = group_start[sorted_pos];
        int count      = group_count[sorted_pos];

        if (count <= 1) {
            result[i] = -1;
            continue;
        }

        int min_dist = n;

        int left_idx;
        if (sorted_pos > start) {
            left_idx  = nodes[sorted_pos - 1].idx;
            int d     = q_idx - left_idx;
            if (d < min_dist) min_dist = d;
        } else {
            left_idx  = nodes[start + count - 1].idx;
            int d     = q_idx + (n - left_idx);
            if (d < min_dist) min_dist = d;
        }

        int right_idx;
        if (sorted_pos < start + count - 1) {
            right_idx = nodes[sorted_pos + 1].idx;
            int d     = right_idx - q_idx;
            if (d < min_dist) min_dist = d;
        } else {
            right_idx = nodes[start].idx;
            int d     = (n - q_idx) + right_idx;
            if (d < min_dist) min_dist = d;
        }

        result[i] = min_dist;
    }

    free(nodes);
    free(pos_in_sorted);
    free(group_start);
    free(group_count);

    return result;
}

int main(void) {
    int nums[]    = {3, 1, 3, 2, 3, 5};
    int queries[] = {0, 4};
    int numsSize    = 6;
    int queriesSize = 2;
    int returnSize  = 0;

    int* result = solveQueries(nums, numsSize, queries, queriesSize, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("query[%d] = %d\n", i, result[i]);
    }

    free(result);
    return 0;
}


/*
===========================================================================
  WHAT HAPPENS UNDER THE HOOD — STEP BY STEP
===========================================================================

INPUT STATE
-----------
  nums    = [3, 1, 3, 2, 3, 5]   (indices 0..5)
  queries = [0, 4]
  n       = 6

---------------------------------------------------------------------------
STEP 1 — malloc(nodes), populate
---------------------------------------------------------------------------
  Heap allocates 6 * sizeof(Node) = 48 bytes.
  Each Node is a (val, idx) pair copied straight from nums[].

  nodes[] in memory (before sort):
    [0] {val=3, idx=0}
    [1] {val=1, idx=1}
    [2] {val=3, idx=2}
    [3] {val=2, idx=3}
    [4] {val=3, idx=4}
    [5] {val=5, idx=5}

---------------------------------------------------------------------------
STEP 2 — qsort(nodes, n, sizeof(Node), compareNodes)
---------------------------------------------------------------------------
  compareNodes first sorts by val ascending; ties broken by idx ascending.
  qsort uses an internal divide-and-conquer (typically Introsort or
  a median-of-3 Quicksort).  It swaps Node structs in-place on the heap.

  nodes[] after sort:
    [0] {val=1, idx=1}    <-- singleton group, val=1
    [1] {val=2, idx=3}    <-- singleton group, val=2
    [2] {val=3, idx=0}    <-- group start, val=3
    [3] {val=3, idx=2}    <--   "
    [4] {val=3, idx=4}    <-- group end,   val=3
    [5] {val=5, idx=5}    <-- singleton group, val=5

---------------------------------------------------------------------------
STEP 3 — malloc three lookup arrays (each 6 ints = 24 bytes)
         Walk groups once with the two-pointer current/start pattern
---------------------------------------------------------------------------
  Outer while: current=0
    Inner while: nodes[0].val==1 only → group [0..0], count=1
      pos_in_sorted[ nodes[0].idx ] = pos_in_sorted[1] = 0
    Backfill: group_start[0]=0, group_count[0]=1

  Outer while: current=1
    Inner while: nodes[1].val==2 only → group [1..1], count=1
      pos_in_sorted[ nodes[1].idx ] = pos_in_sorted[3] = 1
    Backfill: group_start[1]=1, group_count[1]=1

  Outer while: current=2
    Inner while: nodes[2..4].val==3 → group [2..4], count=3
      pos_in_sorted[ nodes[2].idx ] = pos_in_sorted[0] = 2
      pos_in_sorted[ nodes[3].idx ] = pos_in_sorted[2] = 3
      pos_in_sorted[ nodes[4].idx ] = pos_in_sorted[4] = 4
    Backfill: group_start[2]=2, group_count[2]=3
              group_start[3]=2, group_count[3]=3
              group_start[4]=2, group_count[4]=3

  Outer while: current=5
    Inner while: nodes[5].val==5 only → group [5..5], count=1
      pos_in_sorted[5] = 5
    Backfill: group_start[5]=5, group_count[5]=1

  Final lookup tables:
    pos_in_sorted = [2, 0, 3, 1, 4, 5]
                     ^  ^  ^  ^  ^  ^
                     |  |  |  |  |  original idx 5 → sorted pos 5
                     |  |  |  |  original idx 4 → sorted pos 4
                     |  |  |  original idx 3 → sorted pos 1
                     |  |  original idx 2 → sorted pos 3
                     |  original idx 1 → sorted pos 0
                     original idx 0 → sorted pos 2

    group_start   = [0, 1, 2, 2, 2, 5]
    group_count   = [1, 1, 3, 3, 3, 1]

---------------------------------------------------------------------------
STEP 4 — malloc result[queriesSize], set *returnSize = 2
---------------------------------------------------------------------------
  Heap allocates 2 * 4 = 8 bytes for result[].

---------------------------------------------------------------------------
QUERY 0 — queries[0] = 0  (asking about nums[0] = 3)
---------------------------------------------------------------------------
  q_idx      = 0
  sorted_pos = pos_in_sorted[0]  = 2
  start      = group_start[2]    = 2
  count      = group_count[2]    = 3   → more than 1, continue

  min_dist starts at n = 6.

  LEFT neighbor check:
    sorted_pos (2) > start (2)?  NO  → wrap-around case
    left_idx = nodes[start + count - 1].idx
             = nodes[2 + 3 - 1].idx
             = nodes[4].idx  = 4
    circular distance = q_idx + (n - left_idx)
                      = 0    + (6 - 4)  = 2
    2 < 6 → min_dist = 2

  RIGHT neighbor check:
    sorted_pos (2) < start+count-1 (4)?  YES
    right_idx = nodes[sorted_pos + 1].idx
              = nodes[3].idx  = 2
    distance  = right_idx - q_idx = 2 - 0 = 2
    2 == 2 → min_dist stays 2

  result[0] = 2

---------------------------------------------------------------------------
QUERY 1 — queries[1] = 4  (asking about nums[4] = 3)
---------------------------------------------------------------------------
  q_idx      = 4
  sorted_pos = pos_in_sorted[4]  = 4
  start      = group_start[4]    = 2
  count      = group_count[4]    = 3   → more than 1, continue

  min_dist = 6.

  LEFT neighbor check:
    sorted_pos (4) > start (2)?  YES
    left_idx = nodes[sorted_pos - 1].idx
             = nodes[3].idx  = 2
    distance = q_idx - left_idx = 4 - 2 = 2
    2 < 6 → min_dist = 2

  RIGHT neighbor check:
    sorted_pos (4) < start+count-1 (4)?  NO  → wrap-around case
    right_idx = nodes[start].idx
              = nodes[2].idx  = 0
    circular distance = (n - q_idx) + right_idx
                      = (6 - 4)    + 0  = 2
    2 == 2 → min_dist stays 2

  result[1] = 2

---------------------------------------------------------------------------
STEP 5 — free all temp heap allocations
---------------------------------------------------------------------------
  free(nodes)         → 48 bytes returned to heap
  free(pos_in_sorted) → 24 bytes returned to heap
  free(group_start)   → 24 bytes returned to heap
  free(group_count)   → 24 bytes returned to heap

  result[] is NOT freed here — ownership is handed back to caller.

---------------------------------------------------------------------------
STEP 6 — main() receives result pointer
---------------------------------------------------------------------------
  printf prints:
    query[0] = 2
    query[1] = 2

  free(result) → 8 bytes returned to heap
  return 0 → OS tears down the process; remaining stack and heap reclaimed.

---------------------------------------------------------------------------
COMPLEXITY SUMMARY
---------------------------------------------------------------------------
  Time:  O(n log n)  — qsort dominates; query loop is O(q)
  Space: O(n)        — four heap arrays proportional to n
         (result excluded — it belongs to the caller)

===========================================================================
*/
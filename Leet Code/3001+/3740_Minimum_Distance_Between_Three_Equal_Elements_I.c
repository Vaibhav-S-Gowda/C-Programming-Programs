#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ---------- Simple open-addressing hash map ---------- */
#define TABLE_SIZE 4096          /* power of 2 for fast modulo */
#define EMPTY      INT_MIN

typedef struct {
    int  key;
    int  first;   /* oldest stored index  */
    int  second;  /* newest stored index  */
    int  count;   /* occurrences seen so far (capped at 2) */
} Entry;

static Entry table[TABLE_SIZE];

static void ht_clear(void) {
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i].key = EMPTY;
}

/* Returns the entry for key, creating it if absent. */
static Entry *ht_get(int key) {
    unsigned h = (unsigned)key & (TABLE_SIZE - 1);
    while (table[h].key != EMPTY && table[h].key != key)
        h = (h + 1) & (TABLE_SIZE - 1);
    if (table[h].key == EMPTY) {
        table[h].key   = key;
        table[h].count = 0;
    }
    return &table[h];
}

/* ---------- Main solution ---------- */
int minimumDistance(int *nums, int numsSize) {
    ht_clear();

    int ans = INT_MAX;

    for (int idx = 0; idx < numsSize; idx++) {
        Entry *e = ht_get(nums[idx]);

        if (e->count == 0) {
            e->first = idx;
            e->count = 1;
        } else if (e->count == 1) {
            e->second = idx;
            e->count  = 2;
        } else {
            /* Third (or more) occurrence: evaluate and slide window */
            int dist = 2 * (idx - e->first);
            if (dist < ans) ans = dist;

            /* Slide: drop oldest, promote second to first */
            e->first  = e->second;
            e->second = idx;
        }
    }

    return (ans == INT_MAX) ? -1 : ans;
}

/* ---------- Main function ---------- */
int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *nums = (int *)malloc(n * sizeof(int));
    if (!nums) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int result = minimumDistance(nums, n);

    printf("Minimum Distance: %d\n", result);

    free(nums);
    return 0;
}
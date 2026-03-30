#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// ─── Simple hash map: int key → int count ───────────────────────────────────
#define HT_SIZE (1 << 18)   // 262144 buckets, power-of-2 for fast modulo
#define HT_EMPTY INT32_MIN

typedef struct {
    int  key;
    int  count;
} Slot;

typedef struct {
    Slot *slots;
} HashMap;

static HashMap *hm_create(void) {
    HashMap *hm = (HashMap *)malloc(sizeof(HashMap));
    hm->slots   = (Slot *)malloc(HT_SIZE * sizeof(Slot));
    for (int i = 0; i < HT_SIZE; i++) hm->slots[i].key = HT_EMPTY;
    return hm;
}

static void hm_free(HashMap *hm) {
    free(hm->slots);
    free(hm);
}

static void hm_clear(HashMap *hm) {
    memset(hm->slots, 0x80, HT_SIZE * sizeof(Slot)); // sets key = 0x80808080 ≈ INT_MIN
}

static inline int hm_bucket(int key) {
    unsigned u = (unsigned)key;
    u = (u ^ (u >> 16)) * 0x45d9f3bU;
    return (int)(u & (HT_SIZE - 1));
}

// Returns current count (0 if absent)
static int hm_get(const HashMap *hm, int key) {
    int b = hm_bucket(key);
    while (hm->slots[b].key != HT_EMPTY) {
        if (hm->slots[b].key == key) return hm->slots[b].count;
        b = (b + 1) & (HT_SIZE - 1);
    }
    return 0;
}

// Add delta to the count of key; removes slot if count reaches 0
static void hm_add(HashMap *hm, int key, int delta) {
    int b = hm_bucket(key);
    while (hm->slots[b].key != HT_EMPTY && hm->slots[b].key != key)
        b = (b + 1) & (HT_SIZE - 1);

    if (hm->slots[b].key == HT_EMPTY) {
        hm->slots[b].key   = key;
        hm->slots[b].count = delta;
    } else {
        hm->slots[b].count += delta;
    }
}
// ─────────────────────────────────────────────────────────────────────────────

/*
 * canRemove – can we remove a cell with value `val` from the section that
 * spans rows [r0..r1] (or cols [c0..c1] for vertical cuts) and keep it
 * connected?
 *
 * Connectivity rules (horizontal cut, section is rows r0..r1, all n cols):
 *   • rows > 1 AND cols > 1  → always safe (interior cell always has 4 neighbours)
 *   • rows == 1              → only if the cell is on a boundary column (col 0 or col n-1)
 *   • cols == 1              → only if the cell is on a boundary row  (row r0 or row r1)
 */
static bool canRemoveH(const HashMap *freq, long long val,
                       int r0, int r1, int n,
                       int **grid) {
    if (val <= 0 || val > INT32_MAX) return false;
    int v = (int)val;
    if (hm_get(freq, v) == 0) return false;

    int rows = r1 - r0 + 1;
    if (rows > 1 && n > 1)  return true;           // 2-D block, always ok
    if (rows == 1)                                  // single row
        return grid[r0][0] == v || grid[r0][n - 1] == v;
    // n == 1: single column
    return grid[r0][0] == v || grid[r1][0] == v;
}

static bool canRemoveV(const HashMap *freq, long long val,
                       int c0, int c1, int m,
                       int **grid) {
    if (val <= 0 || val > INT32_MAX) return false;
    int v = (int)val;
    if (hm_get(freq, v) == 0) return false;

    int cols = c1 - c0 + 1;
    if (m > 1 && cols > 1)  return true;
    if (cols == 1)                                  // single column
        return grid[0][c0] == v || grid[m - 1][c0] == v;
    // m == 1: single row
    return grid[0][c0] == v || grid[0][c1] == v;
}

// ─────────────────────────────────────────────────────────────────────────────

bool canPartitionGrid(int **grid, int m, int *gridColSize) {
    int n = gridColSize[0];

    long long totalSum = 0;
    long long *rowSums = (long long *)calloc(m, sizeof(long long));
    long long *colSums = (long long *)calloc(n, sizeof(long long));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            rowSums[i] += grid[i][j];
            colSums[j] += grid[i][j];
            totalSum   += grid[i][j];
        }

    HashMap *topFreq = hm_create();
    HashMap *botFreq = hm_create();

    // ── Horizontal cuts ──────────────────────────────────────────────────────
    // Initialise botFreq with the whole grid
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            hm_add(botFreq, grid[i][j], 1);

    long long topSum = 0;
    for (int i = 0; i < m - 1; i++) {
        // Move row i from botFreq → topFreq
        for (int j = 0; j < n; j++) {
            hm_add(topFreq, grid[i][j],  1);
            hm_add(botFreq, grid[i][j], -1);
        }
        topSum += rowSums[i];
        long long botSum = totalSum - topSum;

        if (topSum == botSum) goto done_true;

        if (topSum > botSum) {
            // Try to discard a cell from the top section (rows 0..i)
            long long diff = topSum - botSum;
            if (canRemoveH(topFreq, diff, 0, i, n, grid)) goto done_true;
        } else {
            // Try to discard a cell from the bottom section (rows i+1..m-1)
            long long diff = botSum - topSum;
            if (canRemoveH(botFreq, diff, i + 1, m - 1, n, grid)) goto done_true;
        }
    }

    // ── Vertical cuts ────────────────────────────────────────────────────────
    hm_clear(topFreq);
    hm_clear(botFreq);  // reuse as "leftFreq" / "rightFreq"

    for (int j = 0; j < n; j++)
        for (int i = 0; i < m; i++)
            hm_add(botFreq, grid[i][j], 1);

    long long leftSum = 0;
    for (int j = 0; j < n - 1; j++) {
        for (int i = 0; i < m; i++) {
            hm_add(topFreq, grid[i][j],  1);
            hm_add(botFreq, grid[i][j], -1);
        }
        leftSum += colSums[j];
        long long rightSum = totalSum - leftSum;

        if (leftSum == rightSum) goto done_true;

        if (leftSum > rightSum) {
            long long diff = leftSum - rightSum;
            if (canRemoveV(topFreq, diff, 0, j, m, grid)) goto done_true;
        } else {
            long long diff = rightSum - leftSum;
            if (canRemoveV(botFreq, diff, j + 1, n - 1, m, grid)) goto done_true;
        }
    }

    hm_free(topFreq);
    hm_free(botFreq);
    free(rowSums); free(colSums);
    return false;

done_true:
    hm_free(topFreq);
    hm_free(botFreq);
    free(rowSums); free(colSums);
    return true;
}

// ─── Test harness ────────────────────────────────────────────────────────────
static int **makeGrid(int m, int n) {
    int **g = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) g[i] = (int *)malloc(n * sizeof(int));
    return g;
}
static void freeGrid(int **g, int m) {
    for (int i = 0; i < m; i++) free(g[i]);
    free(g);
}

int main(void) {
    // ── Test 1: expected true (equal horizontal cut) ──
    {
        int m = 2, n = 2;
        int **g = makeGrid(m, n);
        int v[2][2] = {{1,4},{2,3}};
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) g[i][j] = v[i][j];
        int cs[] = {n, n};
        printf("Test 1 (expect true ): %s\n", canPartitionGrid(g, m, cs) ? "true" : "false");
        freeGrid(g, m);
    }
    // ── Test 2: expected true (discount from right section) ──
    {
        int m = 2, n = 3;
        int **g = makeGrid(m, n);
        int v[2][3] = {{1,2},{3,4}};   // actually 2×2; fill as 2×3 variant
        // Use the problem example: vertical cut after col 0 → left=1+3=4, right=2+4=6; discard 2
        int v2[2][2] = {{1,2},{3,4}};
        freeGrid(g, m);
        m = 2; n = 2;
        g = makeGrid(m, n);
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) g[i][j] = v2[i][j];
        int cs[] = {n, n};
        printf("Test 2 (expect true ): %s\n", canPartitionGrid(g, m, cs) ? "true" : "false");
        freeGrid(g, m);
    }
    // ── Test 3: original grid from the uploaded code ──
    {
        int m = 3, n = 3;
        int **g = makeGrid(m, n);
        int v[3][3] = {{1,5,11},{5,2,3},{4,6,7}};
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) g[i][j] = v[i][j];
        int cs[] = {n, n, n};
        printf("Test 3 (expect true ): %s\n", canPartitionGrid(g, m, cs) ? "true" : "false");
        freeGrid(g, m);
    }
    // ── Test 4: single-column grid, expected true ──
    {
        int m = 5, n = 1;
        int **g = makeGrid(m, n);
        int v[5][1] = {{1},{3},{2},{2},{1}};
        for (int i = 0; i < m; i++) g[i][0] = v[i][0];
        int cs[] = {1,1,1,1,1};
        printf("Test 4 (expect true ): %s\n", canPartitionGrid(g, m, cs) ? "true" : "false");
        freeGrid(g, m);
    }
    // ── Test 5: should be false ──
    {
        int m = 2, n = 3;
        int **g = makeGrid(m, n);
        int v[2][3] = {{1,2,4},{2,3,5}};
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) g[i][j] = v[i][j];
        int cs[] = {n, n};
        // horiz cut: top=7, bot=10; diff=3, but removing 3 from bot splits it
        printf("Test 5 (expect false): %s\n", canPartitionGrid(g, m, cs) ? "true" : "false");
        freeGrid(g, m);
    }
    return 0;
}

// Compile & run:
// gcc -O2 -Wall 3548_Equal_Sum_Grid_Partition_II.c -o sol && ./sol
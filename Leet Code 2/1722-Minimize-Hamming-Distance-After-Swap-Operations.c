#include <stdio.h>
#include <stdlib.h>

// Union-Find with Path Compression
int find(int* parent, int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent, parent[i]);
}

void unite(int* parent, int i, int j) {
    int rootI = find(parent, i);
    int rootJ = find(parent, j);
    if (rootI != rootJ) parent[rootI] = rootJ;
}

int minimumHammingDistance(int* source, int sourceSize, int* target, int targetSize,
                           int** allowedSwaps, int allowedSwapsSize, int* allowedSwapsColSize) {

    int n = sourceSize;
    int *parent = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) parent[i] = i;

    // 1. Union-Find
    for (int i = 0; i < allowedSwapsSize; i++) {
        unite(parent, allowedSwaps[i][0], allowedSwaps[i][1]);
    }

    // 2. Build components
    int **compIndices = (int**)calloc(n, sizeof(int*));
    int *compSizes = (int*)calloc(n, sizeof(int));
    int *currIdx = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        compSizes[find(parent, i)]++;
    }

    for (int i = 0; i < n; i++) {
        int root = find(parent, i);
        if (compIndices[root] == NULL) {
            compIndices[root] = (int*)malloc(compSizes[root] * sizeof(int));
        }
        compIndices[root][currIdx[root]++] = i;
    }

    // 3. Match using frequency
    int totalMatches = 0;
    int *freq = (int*)calloc(100001, sizeof(int));

    for (int i = 0; i < n; i++) {
        if (compSizes[i] > 0) {
            for (int j = 0; j < compSizes[i]; j++) {
                freq[source[compIndices[i][j]]]++;
            }
            for (int j = 0; j < compSizes[i]; j++) {
                int val = target[compIndices[i][j]];
                if (freq[val] > 0) {
                    totalMatches++;
                    freq[val]--;
                }
            }
            for (int j = 0; j < compSizes[i]; j++) {
                freq[source[compIndices[i][j]]] = 0;
            }
            free(compIndices[i]);
        }
    }

    free(parent);
    free(compSizes);
    free(compIndices);
    free(currIdx);
    free(freq);

    return n - totalMatches;
}

int main() {
    int source[] = {1, 2, 3, 4};
    int target[] = {2, 1, 4, 5};

    int n = 4;

    // allowedSwaps = [[0,1], [2,3]]
    int swaps0[] = {0, 1};
    int swaps1[] = {2, 3};

    int* allowedSwaps[] = {swaps0, swaps1};
    int allowedSwapsSize = 2;

    int allowedSwapsColSize[] = {2, 2};

    int result = minimumHammingDistance(
        source, n,
        target, n,
        allowedSwaps, allowedSwapsSize,
        allowedSwapsColSize
    );

    printf("Minimum Hamming Distance: %d\n", result);

    return 0;
}
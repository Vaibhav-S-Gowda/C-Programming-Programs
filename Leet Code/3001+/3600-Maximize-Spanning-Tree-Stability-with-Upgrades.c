#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

enum {U, V, S, M};

// --- DSU Implementation ---
int find(int *parent, int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent, parent[x]); // Recursive path compression
}

void join(int *parent, int *rank, int u, int v) {
    int pu = find(parent, u), pv = find(parent, v);
    if (pu != pv) {
        if (rank[pu] < rank[pv]) parent[pu] = pv;
        else if (rank[pu] > rank[pv]) parent[pv] = pu;
        else {
            parent[pv] = pu;
            rank[pu]++;
        }
    }
}

// --- Logic Check for Binary Search ---
bool canAchieve(int mid, int n, int** edges, int edgesSize, int k) {
    int parent[n], rank[n];
    for (int i = 0; i < n; i++) { parent[i] = i; rank[i] = 0; }
    
    int components = n;

    // Pass 1: Mandatory edges and edges already >= mid
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][U], v = edges[i][V], s = edges[i][S], m = edges[i][M];
        if (m == 1) {
            if (s < mid) return false; // Mandatory edge fails stability
            if (find(parent, u) != find(parent, v)) {
                join(parent, rank, u, v);
                components--;
            }
        } else if (s >= mid) {
            if (find(parent, u) != find(parent, v)) {
                join(parent, rank, u, v);
                components--;
            }
        }
    }

    // Pass 2: Optional edges that need upgrade to reach mid (s*2 >= mid)
    for (int i = 0; i < edgesSize && k > 0; i++) {
        int u = edges[i][U], v = edges[i][V], s = edges[i][S], m = edges[i][M];
        if (m == 0 && s < mid && (s * 2) >= mid) {
            if (find(parent, u) != find(parent, v)) {
                join(parent, rank, u, v);
                components--;
                k--;
            }
        }
    }

    return components == 1;
}

int maxStability(int n, int** edges, int edgesSize, int* edgesColSize, int k) {
    // Basic connectivity check: mandatory edges must not form a cycle
    int p[n], r[n];
    for(int i=0; i<n; i++) { p[i]=i; r[i]=0; }
    for(int i=0; i<edgesSize; i++) {
        if(edges[i][M] == 1) {
            if(find(p, edges[i][U]) == find(p, edges[i][V])) return -1;
            join(p, r, edges[i][U], edges[i][V]);
        }
    }

    int low = 0, high = 2000000, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (mid == 0) { low = 1; continue; }
        if (canAchieve(mid, n, edges, edgesSize, k)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

// --- Main Function for Testing ---
int main() {
    int n = 5;
    int k = 1;
    // Input format: {u, v, strength, mandatory}
    int rawEdges[][4] = {
        {0, 1, 10, 1},
        {1, 2, 5, 0},
        {2, 3, 4, 0},
        {3, 4, 10, 1},
        {0, 4, 2, 0}
    };
    int edgesSize = sizeof(rawEdges) / sizeof(rawEdges[0]);
    
    // Allocating int** for LeetCode compatibility
    int** edges = (int**)malloc(edgesSize * sizeof(int*));
    for (int i = 0; i < edgesSize; i++) {
        edges[i] = (int*)malloc(4 * sizeof(int));
        for (int j = 0; j < 4; j++) edges[i][j] = rawEdges[i][j];
    }
    int edgesColSize = 4;

    int result = maxStability(n, edges, edgesSize, &edgesColSize, k);
    printf("Maximum Stability: %d\n", result);

    // Cleanup
    for (int i = 0; i < edgesSize; i++) free(edges[i]);
    free(edges);

    return 0;
}
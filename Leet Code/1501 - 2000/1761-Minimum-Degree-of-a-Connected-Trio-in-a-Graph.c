#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Using static to move the large matrix off the stack
static bool adj[401][401];

int minTrioDegree(int n, int** edges, int edgesSize, int* edgesColSize) {
    // Reset arrays (crucial if calling multiple times)
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) adj[i][j] = false;
    }
    int degree[401] = {0};
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][v] = adj[v][u] = true;
        degree[u]++;
        degree[v]++;
    }
    
    int min_degree = INT_MAX;
    bool found = false;
    
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (!adj[i][j]) continue;
            
            // Optimization: if current pair degree already exceeds min_degree, skip k
            if (degree[i] + degree[j] - 6 >= min_degree) continue; 

            for (int k = j + 1; k <= n; k++) {
                if (adj[i][k] && adj[j][k]) {
                    found = true;
                    int current_degree = (degree[i] + degree[j] + degree[k]) - 6;
                    min_degree = MIN(min_degree, current_degree);
                }
            }
        }
    }
    
    return found ? min_degree : -1;
}

int main() {
    int n = 6;
    int e1[] = {1, 2}, e2[] = {1, 3}, e3[] = {3, 2}, e4[] = {4, 1}, e5[] = {5, 2}, e6[] = {3, 6};
    int* edges[] = {e1, e2, e3, e4, e5, e6};
    int edgesSize = 6;
    int edgesColSize = 2;

    int result = minTrioDegree(n, edges, edgesSize, &edgesColSize);
    printf("Minimum Trio Degree: %d\n", result); // Expected: 3

    return 0;
}
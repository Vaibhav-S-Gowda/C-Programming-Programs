#include <stdio.h>
#include <stdlib.h>

int dfs(int node, int** adj, int* adjSize, int* state, int* result, int* pos) {
    if (state[node] == 1) return 0; // cycle
    if (state[node] == 2) return 1;

    state[node] = 1;

    for (int i = 0; i < adjSize[node]; i++) {
        if (!dfs(adj[node][i], adj, adjSize, state, result, pos))
            return 0;
    }

    state[node] = 2;
    result[(*pos)--] = node;
    return 1;
}

int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize, int* returnSize) {
    
    int** adj = (int**)malloc(numCourses * sizeof(int*));
    int* adjSize = (int*)calloc(numCourses, sizeof(int));

    // count edges
    for (int i = 0; i < prerequisitesSize; i++) {
        adjSize[prerequisites[i][1]]++;
    }

    // allocate
    for (int i = 0; i < numCourses; i++) {
        adj[i] = (int*)malloc(adjSize[i] * sizeof(int));
        adjSize[i] = 0;
    }

    // fill
    for (int i = 0; i < prerequisitesSize; i++) {
        int a = prerequisites[i][0];
        int b = prerequisites[i][1];
        adj[b][adjSize[b]++] = a;
    }

    int* result = (int*)malloc(numCourses * sizeof(int));
    int* state = (int*)calloc(numCourses, sizeof(int));
    int pos = numCourses - 1;

    for (int i = 0; i < numCourses; i++) {
        if (state[i] == 0) {
            if (!dfs(i, adj, adjSize, state, result, &pos)) {
                *returnSize = 0;

                // free memory before returning
                for (int j = 0; j < numCourses; j++) free(adj[j]);
                free(adj);
                free(adjSize);
                free(state);

                return NULL;
            }
        }
    }

    *returnSize = numCourses;

    // free adjacency + state (result must be returned)
    for (int i = 0; i < numCourses; i++) free(adj[i]);
    free(adj);
    free(adjSize);
    free(state);

    return result;
}

int main() {
    int numCourses = 4;

    int p0[] = {1, 0};
    int p1[] = {2, 0};
    int p2[] = {3, 1};
    int p3[] = {3, 2};

    int* prerequisites[] = {p0, p1, p2, p3};
    int returnSize;

    int* order = findOrder(numCourses, prerequisites, 4, &returnSize);

    if (order == NULL) {
        printf("Cycle detected. No valid ordering.\n");
        return 0;
    }

    printf("Course Order: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", order[i]);
    }
    printf("\n");

    free(order);
    return 0;
}
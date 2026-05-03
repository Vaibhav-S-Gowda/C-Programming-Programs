#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize) {
    int* inDegree = calloc(numCourses, sizeof(int));
    int* counts = calloc(numCourses, sizeof(int));

    for (int i = 0; i < prerequisitesSize; i++) {
        inDegree[prerequisites[i][0]]++;
        counts[prerequisites[i][1]]++;
    }

    int** adj = malloc(numCourses * sizeof(int*));
    for (int i = 0; i < numCourses; i++) {
        adj[i] = counts[i] ? malloc(counts[i] * sizeof(int)) : NULL;
        counts[i] = 0;
    }

    for (int i = 0; i < prerequisitesSize; i++) {
        int u = prerequisites[i][1];
        int v = prerequisites[i][0];
        adj[u][counts[u]++] = v;
    }

    int* queue = malloc(numCourses * sizeof(int));
    int head = 0, tail = 0;

    for (int i = 0; i < numCourses; i++) {
        if (inDegree[i] == 0) {
            queue[tail++] = i;
        }
    }

    int visitedCount = 0;

    while (head < tail) {
        int curr = queue[head++];
        visitedCount++;

        for (int i = 0; i < counts[curr]; i++) {
            int neighbor = adj[curr][i];
            if (--inDegree[neighbor] == 0) {
                queue[tail++] = neighbor;
            }
        }
    }

    for (int i = 0; i < numCourses; i++) {
        if (adj[i]) free(adj[i]);
    }
    free(adj);
    free(inDegree);
    free(counts);
    free(queue);

    return visitedCount == numCourses;
}

int main() {
    int numCourses = 2;

    int p0[] = {1, 0};
    int* prerequisites[] = {p0};

    bool result = canFinish(numCourses, prerequisites, 1);

    if (result)
        printf("Can finish all courses\n");
    else
        printf("Cannot finish (cycle detected)\n");

    return 0;
}
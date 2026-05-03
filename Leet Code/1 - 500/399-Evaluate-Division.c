#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NODES 40

typedef struct {
    int to;
    double weight;
} Edge;

typedef struct {
    Edge edges[MAX_NODES];
    int count;
    char name[20];
} Node;

Node graph[MAX_NODES];
int nodeCount = 0;

int get_node_index(char* name) {
    for (int i = 0; i < nodeCount; i++) {
        if (strcmp(graph[i].name, name) == 0)
            return i;
    }

    if (nodeCount >= MAX_NODES) {
        printf("Error: node limit exceeded\n");
        exit(1);
    }

    strcpy(graph[nodeCount].name, name);
    graph[nodeCount].count = 0;
    return nodeCount++;
}

double dfs(int curr, int target, bool visited[], double product) {
    if (curr == target) return product;

    visited[curr] = true;

    for (int i = 0; i < graph[curr].count; i++) {
        int next = graph[curr].edges[i].to;

        if (!visited[next]) {
            double res = dfs(next, target, visited,
                             product * graph[curr].edges[i].weight);

            if (res > 0.0) return res;
        }
    }
    return -1.0;
}

double* calcEquation(char*** equations, int equationsSize,
                     double* values,
                     char*** queries, int queriesSize,
                     int* returnSize) {

    nodeCount = 0;

    for (int i = 0; i < MAX_NODES; i++) {
        graph[i].count = 0;
    }

    // Build graph
    for (int i = 0; i < equationsSize; i++) {
        int u = get_node_index(equations[i][0]);
        int v = get_node_index(equations[i][1]);

        graph[u].edges[graph[u].count++] = (Edge){v, values[i]};
        graph[v].edges[graph[v].count++] = (Edge){u, 1.0 / values[i]};
    }

    double* results = malloc(sizeof(double) * queriesSize);
    *returnSize = queriesSize;

    for (int i = 0; i < queriesSize; i++) {
        int start = -1, end = -1;

        for (int j = 0; j < nodeCount; j++) {
            if (strcmp(graph[j].name, queries[i][0]) == 0) start = j;
            if (strcmp(graph[j].name, queries[i][1]) == 0) end = j;
        }

        if (start == -1 || end == -1) {
            results[i] = -1.0;
        } else if (start == end) {
            results[i] = 1.0;
        } else {
            bool visited[MAX_NODES] = {false};
            results[i] = dfs(start, end, visited, 1.0);
        }
    }

    return results;
}

int main() {
    // Simple test case
    char* eq1[] = {"a", "b"};
    char* eq2[] = {"b", "c"};
    char** equations[] = {eq1, eq2};

    double values[] = {2.0, 3.0};

    char* q1[] = {"a", "c"};
    char* q2[] = {"b", "a"};
    char* q3[] = {"a", "e"};
    char* q4[] = {"a", "a"};
    char** queries[] = {q1, q2, q3, q4};

    int returnSize;

    double* result = calcEquation(equations, 2, values, queries, 4, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%.5f ", result[i]);
    }

    free(result);
    return 0;
}
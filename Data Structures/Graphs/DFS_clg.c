#include <stdio.h>
#include <stdbool.h>

#define MAX 10   // max number of vertices

void dfs(int graph[MAX][MAX], bool visited[], int node, int numNodes) {
    visited[node] = true;
    printf("%d ", node);

    for (int neighbor = 0; neighbor < numNodes; neighbor++) {
        // Check if an edge exists and the neighbor is NOT visited
        if (graph[node][neighbor] == 1 && !visited[neighbor]) {
            dfs(graph, visited, neighbor, numNodes);
        }
    }
}

int main() {
    int numNodes;

    printf("Enter number of vertices: ");
    scanf("%d", &numNodes);

    int graph[MAX][MAX];

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    bool visited[MAX] = {false};

    int startNode;
    printf("Enter starting node for DFS: ");
    scanf("%d", &startNode);

    printf("DFS Traversal: ");
    dfs(graph, visited, startNode, numNodes);

    return 0;
}

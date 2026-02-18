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

/*
Technical Notes:

Time Complexity:
- DFS Traversal using Adjacency Matrix: O(V^2)
  Reason: For each vertex, all V neighbors are checked in the adjacency matrix.

Space Complexity:
- Visited Array: O(V)
- Recursion Stack (Worst Case): O(V)
- Adjacency Matrix Storage: O(V^2)

Overall Space Complexity: O(V^2)

Performance Characteristics:
- Efficient for dense graphs.
- Slower for sparse graphs compared to adjacency list implementation.

Algorithm Characteristics:
- Depth First Search uses recursion (implicit stack).
- Explores graph branch-by-branch before backtracking.
- Guarantees visiting all reachable vertices from start node.

Reliability Considerations:
- Risk of stack overflow for very deep or large graphs.
- Input validation not implemented (node bounds, matrix correctness).

Limitations:
- MAX limits graph size to 10 vertices.
- Fixed memory allocation.
- No handling for disconnected graph traversal (only reachable nodes from start).

Possible Optimizations:
- Use adjacency list to reduce space to O(V + E).
- Convert recursion to iterative stack-based DFS.
- Add input validation and boundary checks.

Typical Use Cases:
- Graph connectivity checking
- Cycle detection (with modification)
- Path existence problems
- Topological sorting (directed graphs with modification)
*/
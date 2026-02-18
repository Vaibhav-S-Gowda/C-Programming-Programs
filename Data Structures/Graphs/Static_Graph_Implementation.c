#include <stdio.h>
#define MAX 10

struct Graph {
    int vertices;
    int adj[MAX][MAX];
};

void initGraph(struct Graph *g, int v) {
    g->vertices = v;
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            g->adj[i][j] = 0;
}

void addEdge(struct Graph *g, int src, int dest) {
    g->adj[src][dest] = 1;
    g->adj[dest][src] = 1;
}

void display(struct Graph *g) {
    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            printf("%d ", g->adj[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct Graph g;
    initGraph(&g, 4);

    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 3);

    printf("Adjacency Matrix:\n");
    display(&g);

    return 0;
}

/*
Technical Notes:

Time Complexity:
- Graph Initialization (initGraph): O(V^2)
  Reason: Initializes entire adjacency matrix.

- Add Edge (addEdge): O(1)
  Reason: Direct index assignment in matrix.

- Display Graph (display): O(V^2)
  Reason: Prints every matrix element.

Overall Complexity (Typical Run): O(V^2)

Space Complexity:
- Adjacency Matrix Storage: O(V^2)
- Structure Overhead: O(1)

Overall Space Complexity: O(V^2)

Performance Characteristics:
- Fast edge lookup → O(1)
- Best suited for dense graphs.
- Memory inefficient for sparse graphs.

Design Characteristics:
- Uses static memory allocation (fixed MAX size).
- Undirected graph representation (symmetric matrix).
- Simple and predictable memory layout.

Reliability Considerations:
- No boundary checking for src/dest vertex indices.
- No validation for MAX overflow.
- Assumes valid vertex input.

Limitations:
- Graph size limited by MAX (10 vertices).
- Cannot dynamically resize.
- Not efficient for large-scale graph storage.

Possible Optimizations:
- Switch to adjacency list → reduces space to O(V + E).
- Add bounds checking for safe edge insertion.
- Support dynamic memory allocation.

Typical Use Cases:
- Small graph simulations.
- Educational graph algorithm demonstrations.
- Network topology prototypes (small scale).
*/

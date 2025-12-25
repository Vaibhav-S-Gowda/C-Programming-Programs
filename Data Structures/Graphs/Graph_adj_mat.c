#include <stdio.h>
#include <stdlib.h>

/* Graph structure */
typedef struct {
    int numVertices;
    int **adjMatrix;
} *Graph;

Graph createGraph(int vertices) {
    Graph graph = malloc(sizeof(*graph));
    graph->numVertices = vertices;

    graph->adjMatrix = malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(Graph graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

void displayGraph(Graph graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void freeGraph(Graph graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);
}

int main() {
    Graph graph = createGraph(4);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);

    printf("Adjacency Matrix:\n");
    displayGraph(graph);

    freeGraph(graph);
    return 0;
}

/* | Operation         | Complexity |
   | ----------------- | ---------- |
   | Add Edge          | O(1)       |
   | Check Adjacency   | O(1)       |
   | Display Graph     | O(n²)      |
   | Space Requirement | O(n²)      | */


/*graph
    |
    v
    +---------------------+
    | numVertices = 4     |
    | adjMatrix ----------+----+
    +---------------------+    |
                               v
                +------+  +------+  +------+  +------+
    adjMatrix ->|  *   |->|  *   |->|  *   |->|  *   |
                +------+  +------+  +------+  +------+
                |         |         |         |
                v         v         v         v
               +----+----+----+----+
    Row 0 -->  | 0  | 0  | 0  | 0  |
               +----+----+----+----+
               +----+----+----+----+
    Row 1 -->  | 0  | 0  | 0  | 0  |
               +----+----+----+----+
               +----+----+----+----+
    Row 2 -->  | 0  | 0  | 0  | 0  |
               +----+----+----+----+
               +----+----+----+----+
    Row 3 -->  | 0  | 0  | 0  | 0  |
               +----+----+----+----+



    Adjacency Matrix:

      0   1   2   3
    +---+---+---+---+
0   | 0 | 1 | 1 | 0 |
    +---+---+---+---+
1   | 1 | 0 | 0 | 1 |
    +---+---+---+---+
2   | 1 | 0 | 0 | 0 |
    +---+---+---+---+
3   | 0 | 1 | 0 | 0 |
    +---+---+---+---+

*/
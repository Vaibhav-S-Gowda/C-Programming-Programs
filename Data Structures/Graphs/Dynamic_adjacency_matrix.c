#include <stdio.h>
#include <stdlib.h>

/* Graph ADT */
typedef struct {
    int numVertices;
    int **adjMatrix;
} Graph;

/* Create graph with dynamic adjacency matrix */
Graph *createGraph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjMatrix = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int *)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    return graph;
}

/* Add edge (Undirected graph) */
void addEdge(Graph *graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

/* Display adjacency matrix */
void displayGraph(const Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

/* Free allocated memory */
void freeGraph(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);
}

/* Main function */
int main() {
    int vertices = 4;

    Graph *graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);

    printf("Adjacency Matrix:\n");
    displayGraph(graph);

    freeGraph(graph);
    return 0;
}

/*
Uses dynamic memory allocation
int **adjMatrix;  represents a 2D matrix in heap
Space complexity: O(V²)
Edge insertion: O(1)
Suitable for dense graphs*/
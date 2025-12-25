#include <stdio.h>
#include <stdlib.h>

// Graph structure
typedef struct {
    int numVertices;
    int **adjMatrix;
} *Graph;

// Function to create a graph with V vertices
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

// Adds an undirected edge (src <-> dest)
void addEdge(Graph graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

// Print adjacency matrix
void printGraph(Graph graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Free allocated memory
void freeGraph(Graph graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);
}

// Main function
int main() {
    int numVertices = 4;
    Graph graph = createGraph(numVertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);

    printGraph(graph);

    freeGraph(graph);
    return 0;
}

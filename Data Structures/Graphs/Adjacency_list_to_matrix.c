#include <stdio.h>
#include <stdlib.h>

typedef struct AdjNode {
    int vertex;
    int weight;                 /* Use 1 for unweighted graphs */
    struct AdjNode *next;
} AdjNode;

typedef struct {
    int vertexCount;
    AdjNode **adjList;
} Graph;

int **createAdjacencyMatrix(int vertices) {
    int **matrix = (int **)malloc(vertices * sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < vertices; i++) {
        matrix[i] = (int *)calloc(vertices, sizeof(int));
        if (matrix[i] == NULL) {
            return NULL;
        }
    }
    return matrix;
}

Graph *createGraph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertexCount = vertices;

    graph->adjList = (AdjNode **)malloc(vertices * sizeof(AdjNode *));
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}


int **convertListToMatrix(const Graph *graph) {
    if (graph == NULL || graph->adjList == NULL) {
        return NULL;
    }

    int **matrix = createAdjacencyMatrix(graph->vertexCount);
    if (matrix == NULL) {
        return NULL;
    }

    for (int src = 0; src < graph->vertexCount; src++) {
        AdjNode *current = graph->adjList[src];

        while (current != NULL) {
            matrix[src][current->vertex] = current->weight;
            current = current->next;
        }
    }
    return matrix;
}

void printAdjacencyMatrix(int **matrix, int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeAdjacencyMatrix(int **matrix, int vertices) {
    if (matrix == NULL) return;

    for (int i = 0; i < vertices; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void addEdge(Graph *graph, int src, int dest, int weight) {
    AdjNode *newNode = (AdjNode *)malloc(sizeof(AdjNode));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

int main() {
    int vertices = 5;
    Graph *graph = createGraph(vertices);

    addEdge(graph, 0, 1, 6);
    addEdge(graph, 0, 3, 7);
    addEdge(graph, 1, 2, 5);
    addEdge(graph, 1, 3, 8);
    addEdge(graph, 1, 4, -4);
    addEdge(graph, 2, 1, -2);
    addEdge(graph, 3, 2, -3);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 4, 0, 2);
    addEdge(graph, 4, 2, 7);

    int **matrix = convertListToMatrix(graph);

    printf("Adjacency Matrix:\n");
    printAdjacencyMatrix(matrix, vertices);

    freeAdjacencyMatrix(matrix, vertices);
    return 0;
}


/*  | Aspect       | Complexity   |
    | ------------ | ------------ |
    | Conversion   | **O(V + E)** |
    | Matrix Space | **O(V²)**    | */

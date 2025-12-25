#include <stdio.h>
#include <stdlib.h>

/* Node for adjacency list */
typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

/* Graph structure */
typedef struct {
    int numVertices;
    Node **adjList;
} *Graph;

Graph createGraph(int vertices) {
    Graph graph = malloc(sizeof(*graph));
    graph->numVertices = vertices;

    graph->adjList = malloc(vertices * sizeof(Node *));
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph graph, int src, int dest) {
    Node *newNode = malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

void displayGraph(Graph graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Vertex %d:", i);
        Node *temp = graph->adjList[i];
        while (temp != NULL) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    Graph graph = createGraph(5);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 3, 1);

    printf("Directed Sparse Graph:\n");
    displayGraph(graph);

    return 0;
}

// Edge stored only in one direction

// Space complexity: O(V + E)

// Efficient for sparse directed graphs
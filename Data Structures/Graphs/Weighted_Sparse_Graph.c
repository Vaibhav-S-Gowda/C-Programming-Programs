#include <stdio.h>
#include <stdlib.h>

/* Node with weight */
typedef struct Node {
    int vertex;
    int weight;
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

void addEdge(Graph graph, int src, int dest, int weight) {
    /* src -> dest */
    Node *newNode = malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    /* dest -> src */
    newNode = malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->weight = weight;
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void displayGraph(Graph graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Vertex %d:", i);
        Node *temp = graph->adjList[i];
        while (temp != NULL) {
            printf(" -> %d(%d)", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    Graph graph = createGraph(4);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 5);
    addEdge(graph, 1, 3, 3);
    addEdge(graph, 2, 3, 8);

    printf("Weighted Sparse Graph:\n");
    displayGraph(graph);

    return 0;
}

// Each edge stores a weight

// Efficient for road networks, cost graphs

// Space complexity: O(V + E)
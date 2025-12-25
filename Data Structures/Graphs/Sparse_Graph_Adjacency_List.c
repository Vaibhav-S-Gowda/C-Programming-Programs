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

Node *createNode(int v) {
    Node *newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph graph, int src, int dest) {
    /* Add edge src -> dest */
    Node *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    /* Add edge dest -> src */
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
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

void freeGraph(Graph graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node *temp = graph->adjList[i];
        while (temp != NULL) {
            Node *toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(graph->adjList);
    free(graph);
}

int main() {
    Graph graph = createGraph(5);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printf("Adjacency List Representation:\n");
    displayGraph(graph);

    freeGraph(graph);
    return 0;
}

// Uses Adjacency List, not a matrix

// Space complexity: O(V + E)

// Efficient when E ≪ V²

// Matches your Graph ADT pointer-based structure
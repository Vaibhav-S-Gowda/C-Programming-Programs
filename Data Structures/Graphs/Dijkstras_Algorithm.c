// (Using Weighted Sparse Graph – Adjacency List)

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int vertex;
    int weight;
    struct Node *next;
} Node;

typedef struct {
    int numVertices;
    Node **adjList;
} *Graph;

Graph createGraph(int vertices) {
    Graph graph = malloc(sizeof(*graph));
    graph->numVertices = vertices;

    graph->adjList = malloc(vertices * sizeof(Node *));
    for (int i = 0; i < vertices; i++)
        graph->adjList[i] = NULL;

    return graph;
}

void addEdge(Graph graph, int src, int dest, int weight) {
    Node *newNode = malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->weight = weight;
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

int minDistance(int dist[], int visited[], int V) {
    int min = INT_MAX, index = -1;

    for (int i = 0; i < V; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(Graph graph, int src) {
    int V = graph->numVertices;
    int dist[V];
    int visited[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = 1;

        Node *temp = graph->adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int w = temp->weight;

            if (!visited[v] && dist[u] != INT_MAX &&
                dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
            temp = temp->next;
        }
    }

    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d\t%d\n", i, dist[i]);
}

int main() {
    Graph graph = createGraph(5);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 5);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 4, 1, 3);
    addEdge(graph, 4, 2, 9);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 3, 0, 7);

    dijkstra(graph, 0);
    return 0;
}

// Time Complexity (Sparse Graph)
// O((V + E) log V) with priority queue
// O(V²) without heap (this version)
/*  Dijkstra’s algorithm finds the shortest path from a single source to all 
    vertices in a weighted graph with non-negative edges.*/ 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct AdjNode {
    int vertex;
    int weight;                 /* Use 1 for unweighted graphs */
    struct AdjNode *next;
} AdjNode;

typedef struct {
    int vertexCount;
    AdjNode **adjList;
} Graph;

Graph *createGraph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertexCount = vertices;

    graph->adjList = (AdjNode **)malloc(vertices * sizeof(AdjNode *));
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void bellmanFord(const Graph *graph, int source) {
    int V = graph->vertexCount;
    int distance[V];

    /* Step 1: Initialize distances */
    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
    }
    distance[source] = 0;

    /* Step 2: Relax edges V - 1 times */
    for (int i = 1; i <= V - 1; i++) {
        for (int u = 0; u < V; u++) {
            AdjNode *temp = graph->adjList[u];
            while (temp != NULL) {
                int v = temp->vertex;
                int w = temp->weight;

                if (distance[u] != INT_MAX &&
                    distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                }
                temp = temp->next;
            }
        }
    }

    /* Step 3: Check for negative weight cycles */
    for (int u = 0; u < V; u++) {
        AdjNode *temp = graph->adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int w = temp->weight;

            if (distance[u] != INT_MAX &&
                distance[u] + w < distance[v]) {
                printf("Graph contains a negative weight cycle\n");
                return;
            }
            temp = temp->next;
        }
    }

    /* Print results */
    printf("\nBellman-Ford Result (Source = %d):\n", source);
    printf("Vertex\tDistance\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, distance[i]);
    }
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

    /* Create graph */
    Graph *graph = createGraph(vertices);

    /* Add directed weighted edges */
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

    /* Run Bellman-Ford from source vertex 0 */
    bellmanFord(graph, 0);

    return 0;
}



/*  Why Bellman–Ford Uses Adjacency List Well
    - Handles negative edge weights
    - Works correctly on sparse graphs
    - Time complexity: O(V × E)

    Difference from Dijkstra
    - Bellman–Ford detects negative cycles
    - Dijkstra cannot handle negative weights */
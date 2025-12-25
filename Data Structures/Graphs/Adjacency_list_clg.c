#include <stdio.h>
#include <stdlib.h>

typedef struct AdjNode {
    int dest;
    struct AdjNode* next;
} *NODE;

typedef struct Adj {
    NODE head;
} *LIST;

typedef struct myGraph {
    int numVertices;
    LIST array;
} *Graph;

/* FUNCTION: Create new adjacency list node */
NODE newAdjNode(int dest) {
    NODE node = (NODE)malloc(sizeof(struct AdjNode));
    node->dest = dest;
    node->next = NULL;
    return node;
}

/* FUNCTION: Create a graph with V vertices */
Graph createGraph(int vertices) {
    Graph graph = (Graph)malloc(sizeof(struct myGraph));
    graph->numVertices = vertices;

    graph->array = (LIST)malloc(vertices * sizeof(struct Adj));
    for (int i = 0; i < vertices; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}

/* FUNCTION: Add Edge (undirected version) */
void addEdge(Graph graph, int src, int dest) {

    // Add dest to src's adjacency list
    NODE node = newAdjNode(dest);
    node->next = graph->array[src].head; 
    graph->array[src].head = node;

    // Add src to dest's adjacency list (because UNDIRECTED)
    node = newAdjNode(src);
    node->next = graph->array[dest].head;
    graph->array[dest].head = node;
}

/* FUNCTION: Print Graph */
void printGraph(Graph graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        NODE ptr = graph->array[i].head;
        printf("Adjacency list of vertex %d: ", i);
        while (ptr) {
            printf("-> %d ", ptr->dest);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

/* FUNCTION: Free All Allocated Memory */
void freeGraph(Graph graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        NODE curr = graph->array[i].head;
        while (curr) {
            NODE temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

/* MAIN to test */
int main() {
    Graph g = createGraph(5);

    addEdge(g, 0, 1);
    addEdge(g, 0, 4);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 1, 4);
    addEdge(g, 2, 3);
    addEdge(g, 3, 4);

    printGraph(g);

    freeGraph(g);
    return 0;
}


// – Adding an Edge
//      ● Typically O(1), just adding to the list.
// – Checking for Adjacency
//      ● Can take O(V) in the worst case for a vertex with degree V, as we might have
//        to traverse the entire list.
// – Removing an Edge
//      ● Also O(V) in the worst case, as finding the edge to remove may require
//        traversing the list.
/*
| Aspect | Complexity                       |
| ------ | -------------------------------- |
| Time   | O(V²) (Adjacency Matrix)         |
| Space  | O(V) (visited + recursion stack) |

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t vertices;
    int **adjMatrix;
}*Graph;

Graph graph_create(size_t vertices) {
    Graph g = malloc(sizeof *g);
    if (!g) return NULL;

    g->vertices = vertices;
    g->adjMatrix = calloc(vertices, sizeof g->adjMatrix);

    for (size_t i = 0; i < vertices; i++) {
        g->adjMatrix[i] = calloc(vertices, sizeof g->adjMatrix[i]);
    }
    return g;
}

void graph_add_edge(Graph g, size_t u, size_t v) {
    g->adjMatrix[u][v] = 1;
    g->adjMatrix[v][u] = 1;
}

void graph_print(const Graph g) {
    for (size_t i = 0; i < g->vertices; i++) {
        for (size_t j = 0; j < g->vertices; j++) {
            printf("%d ", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void graph_destroy(Graph g) {
    for (size_t i = 0; i < g->vertices; i++) {
        free(g->adjMatrix[i]);
    }
    free(g->adjMatrix);
    free(g);
}

int main(void) {
    Graph g = graph_create(4);
    if (!g) {
        fprintf(stderr, "Failed to create graph\n");
        return 1;
    }

    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 0, 2);
    graph_add_edge(g, 1, 3);

    printf("Adjacency Matrix:\n");
    graph_print(g);

    graph_destroy(g);
    return 0;
}



// Depth First Search traverses a graph by exploring as far as possible along each branch before backtracking.
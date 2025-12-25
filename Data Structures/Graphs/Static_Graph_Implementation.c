#include <stdio.h>
#define MAX 10

struct Graph {
    int vertices;
    int adj[MAX][MAX];
};

void initGraph(struct Graph *g, int v) {
    g->vertices = v;
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            g->adj[i][j] = 0;
}

void addEdge(struct Graph *g, int src, int dest) {
    g->adj[src][dest] = 1;
    g->adj[dest][src] = 1;
}

void display(struct Graph *g) {
    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            printf("%d ", g->adj[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct Graph g;
    initGraph(&g, 4);

    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 3);

    printf("Adjacency Matrix:\n");
    display(&g);

    return 0;
}

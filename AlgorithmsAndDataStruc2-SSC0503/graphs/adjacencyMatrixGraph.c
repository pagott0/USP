#include <stdio.h>
#include <stdlib.h>

#define Vertex int
typedef struct node *Link;
typedef struct graph *Digraph;
#define Graph Digraph

struct node {
  Vertex w;
};


struct graph {
  int V;
  int A;
  int **adj;
};

Graph initGraph(int n) {
  Graph G = (Graph)malloc(sizeof(*G));
  G->V = n;
  G->A = 0;
  G->adj = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    G->adj[i] = (int *)malloc(n * sizeof(int));
  }
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      G->adj[i][j] = 0;
    }
  }
  return G;
}

void destroyGraph(Graph G) {
  if (G != NULL) {
    for (int i; i < G->V; i++) {
      for(int j = 0; j < G->V; j++) {
        G->adj[i][j] = 0;
      }
    }
    free(G->adj);
    free(G);
  }
}


void insertArc(Graph G, Vertex v, Vertex w) {
  if(G->adj[v][w] == 1) {
    return;
  }
  G->adj[v][w] = 1;
  G->A++;
}

void insertEdge(Graph G, Vertex v, Vertex w) {
  insertArc(G, v, w);
  insertArc(G, w, v);
}

void removeArc(Graph G, Vertex v, Vertex w) {
  if (v > G->V) {
    return;
  }
  if (G->adj[v][w] == 0) {
    return;
  }
  G->adj[v][w] = 0;
  G->A--;
}

void removeEgde(Graph G, Vertex v, Vertex w) {
  removeArc(G, v, w);
  removeArc(G, w, v);
}

void printGraph(Graph G) {
  printf("Total of vertices: %d, total of arcs: %d\n", G->V, (G->A / 2));
  for(int i = 0; i < G->V; i++) {
        int timesFirstLinePrinted = 0;
        for(int j = 0; j < G->V; j++) {
            if(G->adj[i][j] == 1) {
                if(timesFirstLinePrinted == 0) {
                  printf("Vertex %d, arcs:", i);
                  timesFirstLinePrinted++;
                } else {
                    printf(",");
                }
                printf(" %d", j);
            }
        }
        printf("\n");
    }
}

int main(void) {
  int n, i, x, y;
  Graph G;
  if (scanf("%d\n", &n) == 1) {
    G = initGraph(n);
    while (scanf("%d %d\n", &x, &y) != EOF) {
      insertEdge(G, x, y);
    }
  }
  printGraph(G);
  return 0;
}
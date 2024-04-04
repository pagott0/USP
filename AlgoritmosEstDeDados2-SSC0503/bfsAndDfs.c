#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Vertex int
typedef struct graph *Digraph;
#define Graph Digraph

//Enzo Vasconcellos Pagotto - NUSP 13632844

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

void dfsAux(Graph G, int v, int *visited) {
  visited[v] = 1;
  printf("visited %d \n", v);

  for(int i = 0; i < G->V; i++) {
    if(G->adj[v][i] == 1 && !visited[i]) {
      dfsAux(G, i, visited);
    }
  }
}

void dfs(Graph G) {
  int visited[G->V];
  for(int i = 0; i < G->V; i++) {
    visited[i] = 0;
  }
  for(int i = 0; i < G->V; i++) {
    if(!visited[i]) {
      dfsAux(G, i, visited);
    }
  }
}

void BFS(Graph G, Vertex x) {
    int *visited = calloc(G->V, sizeof(int));
    int *queue = calloc(G->V, sizeof(int));
    int start = 0, end = 0;

    queue[end++] = x;
    visited[x] = 1;

    while (start != end) {
        int elem = queue[start++];
        printf("visited %d \n", elem);

        for (int i = 0; i < G->V; i++) { 
            if (G->adj[elem][i] == 1 && !visited[i]) {
                queue[end++] = i;
                visited[i] = 1;
            }
        }
    }

    free(queue);
    free(visited); 
}



int main(void) {
  int n, i, x, y;
  Graph G;
  scanf("%d\n", &n);
  G = initGraph(n);
  for(i = 0; i < n; i++) {
    scanf("%d %d\n", &x, &y);
    insertEdge(G, x, y);
  }
  printf("DFS\n");
  dfs(G);
  printf("BFS\n");
  BFS(G, 0);
  /* printGraph(G); */
  return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define ARESTA_INVALIDA - 1

#define true 1
#define false 0

typedef int bool;
typedef float Peso;

typedef struct {
  int numVertices;
  int numArestas;
  Peso** matriz;
} Grafo;

bool inicializaGrafo(Grafo* g, int vertices) {
  if(g == NULL | vertices < 1) return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  g->matriz = (Peso**)malloc(sizeof(Peso*)*vertices);
  for(int x = 0; x < vertices; x++){
    g->matriz[x] = (Peso*)malloc(sizeof(Peso)*vertices);
    for(int y = 0; y < vertices; y++) {
      g->matriz[x][y] = ARESTA_INVALIDA;
    }
  }
  return true;
}

void exibeGrafo(Grafo* g) {
  if(!g) return;
  printf("Imprimindo grafo (vertices: %i, arestas: %i)\n", g->numVertices, g->numArestas);
  for(int x = 0; x < g->numVertices; x++) printf("\t%5i", x);
  printf("\n");
  for(int x = 0; x < g->numVertices; x++) {
    printf("%i", x);
    for(int y = 0; y < g->numVertices; y++) {
      if(g->matriz[x][y] == ARESTA_INVALIDA) printf("    \t");
      else printf("\t%5.2f", g->matriz[x][y]);
    }
    printf("\n");
  }
}

bool liberaGrafo(Grafo* g){
  if(g == NULL) return false;
  for(int x = 0; x < g->numVertices; x++) free(g->matriz[x]);
  free(g->matriz);
  g->numArestas = 0;
  g->numVertices = 0;
  g->matriz = NULL;
  return true;
}

bool insereAresta(Grafo* g, int v1, int v2, Peso valor) {
  if(v1 < 0 || v2 < 0 || v1 > g->numVertices || v2 > g->numVertices || v1 == v2) return false;
  if(g->matriz[v1][v2] == ARESTA_INVALIDA) {
    if(valor != ARESTA_INVALIDA) {
      g->matriz[v1][v2] = valor;
      g->matriz[v2][v1] = valor;
      g->numArestas++;
    }
  } else {
    g->matriz[v1][v2] = valor;
    g->matriz[v2][v1] = valor;
    if(valor == ARESTA_INVALIDA) g->numArestas--;
  }
  return true;
}

bool removeAresta(Grafo* g, int v1, int v2) {
  if(v1 < 0 || v2 < 0 || v1 > g->numVertices || v2 > g->numVertices || g->matriz[v1][v2] == ARESTA_INVALIDA) return false;
  g->matriz[v1][v2] = ARESTA_INVALIDA;
  g->matriz[v2][v1] = ARESTA_INVALIDA;
  g->numArestas--;
  return true;
}

bool arestaExiste(Grafo* g, int v1, int v2) {
  if(v1 < 0 || v2 < 0 || v1 > g->numVertices || v2 > g->numVertices || g->matriz[v1][v2] == ARESTA_INVALIDA) return false;
  return true;
}

int numeroDeVertices(Grafo* g) {
  if (g != NULL) return g->numVertices;
  return -1;
}

int numeroDeArestas(Grafo* g) {
  if (g != NULL) return g->numArestas;
  return -1;
}

bool possuiVizinhos(Grafo* g, int v) {
  if(!g || v < 0 || v >= g->numVertices) return false;
  for(int x = 0; x < g->numVertices; x++) {
    if(g->matriz[v][x] != ARESTA_INVALIDA) return true;
  }
  return false;
}

int retornaGrauDoVertice(Grafo* g, int v) {
   if(!g || v < 0 || v >= g->numVertices) return -1;
   int grau = 0;
   for(int x = 0; x < g->numVertices; x++) {
    if(g->matriz[v][x] != ARESTA_INVALIDA) grau++;
   }
   return grau;
}
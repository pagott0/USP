#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;
typedef float Peso;

typedef struct aux {
  int vertice;
  struct aux* prox;
  Peso peso;
} ElemList, *PONT;

typedef struct {
  int numVertices;
  int numArestas;
  ElemList** A;
} Grafo;

bool inicializaGrafo(Grafo* g, int vertices){
  if(g == NULL || vertices < 1) return false;
  g->numArestas = 0;
  g->numVertices = vertices;
  g->A = (ElemList**)malloc(sizeof(ElemList*)*vertices);
  for(int x = 0; x < vertices; x++) g->A[x] = NULL;
  return true;
}

void exibeGrafo(Grafo* g) {
  if(!g) return;
  printf("Imprimindo grafo (vertices: %i, arestas: %i)\n", g->numVertices, g->numArestas);
  ElemList* atual;
  for(int x = 0; x < g->numVertices; x++) {
    printf("[%2i]", x);
    atual = g->A[x];
    while(atual) {
      printf(" ->%3i ", atual->vertice);
      atual = atual->prox;
    }
    printf("\n");
  }
}

void liberaGrafo(Grafo* g) {
  if(g == NULL) return;
  ElemList *atual, *apagar;
  for(int x = 0; x < g->numVertices; x++) {
    atual = g->A[x];
    while (atual) {
      apagar = atual;
      atual = atual->prox;
      free(apagar);
    }
  }
  g->numArestas = 0;
  g->numVertices = 0;
  g->A = NULL;
  free(g->A);
  return true;
}

bool insereAresta(Grafo* g, int v1, int v2) {
  if(!g || v1 < 0|| v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices) return false;
  ElemList *novo, *ant = NULL;
  ElemList* atual = g->A[v1];
  while(atual && atual->vertice<v2) {
    ant = atual;
    atual = atual -> prox;
  }
  if(atual && atual->vertice == v2) {
    atual->peso = peso;
    return true;
  }
  novo = (ElemList*)malloc(sizeof(ElemList));
  novo->vertice = v2;
  novo->peso = peso;
  novo->prox = atual;
  if(ant) ant-> prox = novo;
  else g->A[v1] = novo;
  g->numArestas++;
  return true;
}

bool removeAresta(Grafo* g, int v1, int v2) {
  if(!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices) return false;
  ElemList *ant = NULL;
  ElemList* atual = g->A[v1];
  while(atual && atual->vertice < v2) {
    ant = atual;
    atual = atual->prox;
  }
  if(atual && atual->vertice == v2) {
    if(ant) ant->prox = atual->prox;
    else g->A[v1] = atual->prox;
    free(atual);
    g->numArestas--;
    return true;
  }
  return false;
}
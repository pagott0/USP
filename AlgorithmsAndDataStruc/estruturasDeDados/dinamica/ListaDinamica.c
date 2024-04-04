#include "ListaDinamica.h"
#include <stdio.h>
#include <stdlib.h>

static int RemovePosicao(TipoLista *L, TipoApontador p){

  if(P == NULL){
    printf("Posicao invalida\n");
    return POS_INVALIDA;
  }
  
  //unico elemento
  if(p == L->primeiro && p == L->ultimo){
    CriaLista(p);
    free(p);
    return SEM_ERRO;
  }

  //remove do inicio
  if(p == L->primeiro) {
    L->primeiro = L->primeiro->prox;
    free(p);
    return SEM_ERRO;
  }
  
  //remove do meio
  TipoApontador aux = L->primeiro;
  while(aux->prox != NULL && aux->prox != p){
    aux = aux->prox;
  }
  aux->prox = p->prox;

  if (aux->prox == NULL){
    L->ultimo = aux;
  }

  free(p);
  return SEM_ERRO;

  
}

void RemoveLista(TipoLista *L, TipoChave C){
  TipoApontador p = (L, C);
  int e = RemovePosicao(L, p);
  
}


void CriaLista(TipoLista *L){
  L->ultimo = NULL;
  L->primeiro = NULL;
  printf("eh nois\n");
} //passa como referencia pq vai alterar ele

int Insere(TipoLista *L, TipoItem I){

  TipoApontador p;
  p = (TipoApontador) malloc(sizeof(TipoNo));

  if(p == NULL){
    printf("memoria cheia\n");
    return LISTA_CHEIA;
  }
  
  p->item = I;
  p->prox = NULL;
  if(ListaVazia(L)) {
    L->primeiro = p;
    L->ultimo = p;
  }
  else {
    L->ultimo->prox = p;
    L->ultimo = p;

  }

}


TipoApontador Pesquisa(TipoLista *L, TipoChave C){
  TipoApontador p;
  p = L->primeiro;
  while(p != NULL) {
    if(p->item.chave == C){
      return p;
    }
    p = p->prox;
  }
  return p;

  for(a = 0; a <= L->ultimo; a++){
    if(L->itens[a].chave == C){
      return a;
    }
  }
  return NAO_ENCONTROU;
}

char ListaVazia(TipoLista *L){
  return L->primeiro == NULL && L->ultimo == NULL; 
}

char ListaCheia(TipoLista *L);

void ImprimeLista(TipoLista *L){
   TipoApontador a;
  for(a = 0; a <= L->ultimo; a++){
    printf("%d ", L->itens[a].chave)
  }
}


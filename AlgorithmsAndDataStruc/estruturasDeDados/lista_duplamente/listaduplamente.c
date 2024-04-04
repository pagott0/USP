#include "listaduplamente.h"
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
    L->primeiro->ant = NULL;
    free(p);
    return SEM_ERRO;
  }
  
  //remove do meio
  TipoApontador aux = L->primeiro;
  /* while(aux->prox != NULL && aux->prox != p){
    aux = aux->prox;
  } */
  p->ant->prox = p->prox;
/*   aux->prox = p->prox; */

  //remove do fim
  if (p == L->ultimo){
    L->ultimo = p->ant;
  } else{
    p->prox->ant = p->ant;
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
  /* if(ListaVazia(L)) {
    L->primeiro = p;
    L->ultimo = p;
    p->prox = NULL
  }
  else {
    L->ultimo->prox = p;
    L->ultimo = p;

  } */
  if(ListaVazia(L)) {
    L->primeiro = p;
    L->ultimo = p;
    p->prox = NULL;
    p->ant = NULL;
  } else if(L->primeiro->item.chave > I.chave){ //inserir na primeira pos.
    p->prox = L->primeiro;
    L->primeiro->ant = p; 
    L->primeiro = p;
    p->ant = NULL;
  }

   else {
    TipoApontador aux;
    aux = L->primeiro;
    while(aux->prox != NULL && aux->prox->item.chave < I.chave) {
      aux = aux->prox;


    }
    p->prox = aux->prox;
    p->ant = aux;
    aux->prox = p;
    if(p->prox != NULL) { //caso seja o último
      p->prox->ant = p;

    }

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


#include "PilhaDinamica.h"
#include <stdio.h>
#include <stdlib.h>

void RemovePilha(TipoPilha *P, TipoApontador p){

  if(PilhaVazia(P)){
    printf("Pilha vazia\n");
    return;
  }
  
  //unico elemento
  if(P->primeiro->prox == NULL){
    CriaPilha(P);
    free(p);
    return ;
  }

  //remove do inicio
  P->primeiro = P->primeiro->prox;
  free(p);
  

}

TipoItem TopoPilha(TipoPilha *P) {
  if(!PilhaVazia) {
    return P->primeiro->item;
  } 
}



void CriaPilha(TipoPilha *P){
  P->ultimo = NULL;
  P->primeiro = NULL;
  printf("eh nois\n");
} //passa como referencia pq vai alterar ele

int Insere(TipoPilha *P, TipoItem I){

  TipoApontador p;
  p = (TipoApontador) malloc(sizeof(TipoNo));

  if(p == NULL){
    printf("memoria cheia\n");
    return Pilha_CHEIA;
  }
  
  p->item = I;

  if(PilhaVazia(P)) {
    p->prox = NULL;
    P->primeiro = p;

  }
  else {
    p->prox = P->primeiro;
    P->primeiro = p;
    

  }

}


char PilhaVazia(TipoPilha *P){
  return P->primeiro == NULL && L->ultimo == NULL; 
}

char PilhaCheia(TipoPilha *P);

void ImprimePilha(TipoPilha *P){
   TipoApontador a;
  for(a = 0; a <= P->ultimo; a++){
    printf("%d ", P->itens[a].chave)
  }
}


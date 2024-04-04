#ifndef PILHAESTATICA_H
#define PILHAESTATICA_H



#define SEM_ERRO 0
#define POS_INVALIDA -1
#define NAO_ENCONTROU -2
#define PILHA_CHEIA -3

typedef int TipoChave;


typedef struct {
  TipoChave chave;
  //char nome[50]
} TipoItem;

typedef struct TipoNo *TipoApontador;

typedef struct  {
  TipoItem item;
  struct TipoNo *prox;
} TipoNo;

typedef struct{

  TipoApontador primeiro, ultimo;
} TipoPilha;

void CriaPilha(TipoPilha *P); //passa como referencia pq vai alterar ele
int Insere(TipoPilha *P, TipoItem I);
int Remove(TipoPilha *P);
TipoItem TopoPilha(TipoPilha *P);


char PilhaVazia(TipoPilha *P);
char PilhaCheia(TipoPilha *P);

void ImprimePilha(TipoPilha *P);

#endif
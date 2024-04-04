#ifndef LISTAESTATICA_H
#define LISTAESTATICA_H



#define SEM_ERRO 0
#define POS_INVALIDA -1
#define NAO_ENCONTROU -2
#define LISTA_CHEIA -3

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
} TipoLista;

void CriaLista(TipoLista *L); //passa como referencia pq vai alterar ele
int Insere(TipoLista *L, TipoItem I);
int Remove(TipoLista *L, TipoChave C);
int Pesquisa(TipoLista *L, TipoChave C);

char ListaVazia(TipoLista *L);
char ListaCheia(TipoLista *L);

void ImprimeLista(TipoLista *L);

#endif
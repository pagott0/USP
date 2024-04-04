#ifndef SKIPLIST_H
#define SKIPLIST_H

typedef struct No
{
  char chave[11];
  char *valor;
  struct No **proximo;
} No;

typedef struct SkipList
{
  int nivel;
  int tamanho;
  No *header;
} SkipList;

void iniciarSkiplist(SkipList *list);
No *buscaNaLista(SkipList *list, char *key);
int existeNaLista(SkipList *list, char *key);
static int gerarNivelAleatorio();
void inserir(SkipList *list, char *key, char *value);
static void liberarNo(No *x);
void removerItem (SkipList *list, char *key);
void imprimirLista(SkipList *list);



#endif
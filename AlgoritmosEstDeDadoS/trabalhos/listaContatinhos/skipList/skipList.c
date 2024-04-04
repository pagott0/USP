#include <stdio.h>
#include <stdlib.h>
#include "skipList.h"
#include <string.h>

#define NIVEL_MAX_SKIP_LIST 6

void iniciarSkiplist(SkipList *list)
{
  No *header = (No *)malloc(sizeof(No));
  list->header = header;
  strcpy(header->chave, "");

  header->proximo = (No **)malloc((NIVEL_MAX_SKIP_LIST + 1) * sizeof(No *));
  for (int i = 0; i <= NIVEL_MAX_SKIP_LIST; i++)
  {
    header->proximo[i] = list->header;
  }

  list->nivel = 1;
  list->tamanho = 0;
}


int existeNaLista(SkipList *list, char *key)
{
  No *n = buscaNaLista(list, key);
  return n != NULL;
}

static int gerarNivelAleatorio()
{
  int level = 1;
  while (rand() < RAND_MAX / 2 && level < NIVEL_MAX_SKIP_LIST)
  {
    level++;
  }

  return level;
}

No *buscaNaLista(SkipList *list, char *key)
{
  No *x = list->header;

  for (int i = list->nivel; i >= 1; i--)
  {
    while (x->proximo[i] != list->header && strcmp(x->proximo[i]->chave, key) < 0)
    {
      x = x->proximo[i];
    }
  }

  if (x->proximo[1] != list->header && strcmp(x->proximo[1]->chave, key) == 0)
  {
    return x->proximo[1];
  }
  else
  {
    return NULL;
  }
}


void inserir(SkipList *list, char *key, char *value)
{
  No *update[NIVEL_MAX_SKIP_LIST + 1];
  No *x = list->header;
  int level;

  for (int i = list->nivel; i >= 1; i--)
  {
    while (x->proximo[i] != list->header && strcmp(x->proximo[i]->chave, key) < 0)
    {
      x = x->proximo[i];
    }

    update[i] = x;
  }

  if (x->proximo[1] != list->header)
  {
    x = x->proximo[1];
  }

  if (x != list->header && strcmp(key, x->chave) == 0)
  {
    free(x->valor);
    x->valor = strdup(value);
    return;
  }
  else
  {
    level = gerarNivelAleatorio();

    if (level > list->nivel)
    {
      for (int i = list->nivel + 1; i <= level; i++)
      {
        update[i] = list->header;
      }

      list->nivel = level;
    }

    x = (No *)malloc(sizeof(No));
    strcpy(x->chave, key);
    x->valor = strdup(value);
    x->proximo = (No **)malloc(sizeof(No *) * (level + 1));

    for (int i = 1; i <= level; i++)
    {
      x->proximo[i] = update[i]->proximo[i];
      update[i]->proximo[i] = x;
    }

    list->tamanho = list->tamanho + 1;
  }
}

static void liberarNo(No *x)
{
  if (x)
  {
    free(x->proximo);
    free(x);
  }
}

void removerItem(SkipList *list, char *key)
{
  No *update[NIVEL_MAX_SKIP_LIST + 1];
  No *x = list->header;

  for (int i = list->nivel; i >= 1; i--)
  {
    while (x->proximo[i] != list->header && strcmp(x->proximo[i]->chave, key) < 0)
    {
      x = x->proximo[i];
    }

    update[i] = x;
  }

  if (x->proximo[1] != list->header)
  {
    x = x->proximo[1];
  }

  if (x != list->header && strcmp(x->chave, key) == 0)
  {
    for (int i = 1; i <= list->nivel; i++)
    {
      if (update[i]->proximo[i] != x)
      {
        break;
      }

      update[i]->proximo[i] = x->proximo[i];
    }

    free(x->valor);
    liberarNo(x);

    while (list->nivel > 1 && list->header->proximo[list->nivel] == list->header)
    {
      list->nivel--;
    }

    list->tamanho = list->tamanho - 1;
  }
}

void imprimirLista(SkipList *list)
{
  No *x = list->header;
  while (x && x->proximo[1] != list->header)
  {
    printf("%s[%s]->", x->proximo[1]->chave, x->proximo[1]->valor);
    x = x->proximo[1];
  }

  printf("NIL\n");
}
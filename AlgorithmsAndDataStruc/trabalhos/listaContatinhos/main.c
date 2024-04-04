#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./skipList/skipList.h"


int main()
{
  char operacao;

  SkipList lista;
  iniciarSkiplist(&lista);

  for (;;)
  {
    scanf(" %c", &operacao);

    if (operacao == '0')
    {
      break;
    }

    char nome[11];
    char telefone[10];

    switch (operacao)
    {
    case 'I':
      scanf("%s %s", nome, telefone);

      if (existeNaLista(&lista, nome))
      {
        printf("Contatinho ja inserido\n");
        break;
      }

      inserir(&lista, nome, telefone);
      break;
    case 'P':
      scanf("%s", nome);

      No *n = buscaNaLista(&lista, nome);
      if (n == NULL)
      {
        printf("Contatinho nao encontrado\n");
        break;
      }

      printf("Contatinho encontrado: telefone %s\n", n->valor);
      break;
    case 'A':
      scanf("%s %s", nome, telefone);

      if (!existeNaLista(&lista, nome))
      {
        printf("Operacao invalida: contatinho nao encontrado\n");
        break;
      }

      inserir(&lista, nome, telefone);
      break;
    case 'R':
      scanf("%s", nome);

      if (!existeNaLista(&lista, nome))
      {
        printf("Operacao invalida: contatinho nao encontrado\n");
        break;
      }

      removerItem (&lista, nome);
      break;
    default:
      break;
    }
  }

  return 0;
}

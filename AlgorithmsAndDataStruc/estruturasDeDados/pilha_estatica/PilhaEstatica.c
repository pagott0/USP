#include "PilhaEstatica.h"
#include <stdio.h>

void CriaPilha(TipoPilha *P){
  P->ultimo = -1;
  printf("eh nois\n");
} //passa como referencia pq vai alterar ele

int Insere(TipoPilha *P, TipoItem I){
  if(PilhaCheia(P)){
    printf("ta cheia\n");
    return PILHA_CHEIA;
  }
  P->ultimo++;
  P->itens[P->ultimo] = I;

}

int Remove(TipoPilha *P, TipoChave C){
  if(!PilhaVazia){
    P->ultimo--;

  }

} 



TipoItem TopoPilha() {
  if(!PilhaVazia){
    return P->itens[P->ultimo];
  }
  TipoItem I;
  I.chave = -1;
  return I;
}

char PilhaVazia(TipoPilha *P){
  return P->ultimo == -1;
}
char PilhaCheia(TipoPilha *P){
  return P->ultimo == MAXTAM-1;
}

void ImprimePilha(TipoPilha *P){
   TipoApontador a;
  for(a = P->ultimo; a >= 0; a--){
    printf("%d ", P->itens[a].chave)
  }
}


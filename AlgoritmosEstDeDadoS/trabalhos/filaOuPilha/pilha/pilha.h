#ifndef PILHA_H
#define PILHA_H

typedef struct Pilha {
    int tamanho;
    int indiceUltimo;
    int* vetor;
} Pilha;

void iniciarPilha(Pilha* pilha, int tamanho);
void push(Pilha* pilha, int valor);
int pop(Pilha* pilha);
void limparPilha(Pilha* pilha);

#endif
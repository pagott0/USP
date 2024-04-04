#ifndef FILA_H
#define FILA_H

typedef struct Fila {
    int tamanho;
    int indiceUltimo;
    int* vetor;
} Fila;

void iniciarFila(Fila* fila, int tamanho);
void pushFila(Fila* fila, int valor);
int popFila(Fila* fila);
void limparFila(Fila* fila);

#endif
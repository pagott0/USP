#include <stdlib.h>
#include "fila.h"

void iniciarFila(Fila* fila, int tamanho) {
    fila->tamanho = tamanho;
    fila->vetor = (int *) malloc(tamanho * sizeof(int));
    fila->indiceUltimo = -1;

}

void pushFila(Fila* fila, int valor){
    fila->vetor[fila->indiceUltimo + 1] = valor;
    fila->indiceUltimo = fila->indiceUltimo + 1;
    fila->tamanho = fila->tamanho + 1;
}

int popFila(Fila* fila) {
    int itemRemovido = fila->vetor[0]; 
    for(int i = 0; i < fila->indiceUltimo; i++) {
        fila->vetor[i] = fila->vetor[i + 1];
    }
    fila->indiceUltimo = fila->indiceUltimo - 1;
    fila->tamanho = fila->tamanho - 1;

    return itemRemovido;
}

void limparFila(Fila* fila) {
    // Libera a memória alocada para o vetor
    free(fila->vetor);
    
    // Reinicializa os valores da fila
    fila->vetor = NULL;
    fila->tamanho = 0;
    fila->indiceUltimo = -1;
}

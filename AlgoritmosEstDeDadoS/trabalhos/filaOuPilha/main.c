#include <stdio.h>

#include "./fila/fila.h"
#include "./pilha/pilha.h"

struct possibilidades {
    int podeSerFila;
    int podeSerPilha;
};

int main() {
    int numeroCasos;
    scanf("%d", &numeroCasos);

    for (int i = 0; i < numeroCasos; i++) {
        struct possibilidades casosPosiveis = {1, 1};
        int numeroOperacoes;
        scanf("%d", &numeroOperacoes);

        Fila fila;
        Pilha pilha;
        
        iniciarFila(&fila, numeroOperacoes);
        iniciarPilha(&pilha, numeroOperacoes);

        for (int j = 0; j < numeroOperacoes; j++) {
            char operacao;
            int valor;
            scanf(" %c %d", &operacao, &valor);

            if (operacao == 'i') {
                push(&pilha, valor);
                pushFila(&fila, valor);
            } else {
                int valorRemovidoPilha = pop(&pilha);
                int valorRemovidoFila = popFila(&fila);

                if (valorRemovidoPilha != valor) {
                    casosPosiveis.podeSerPilha = 0;
                }
                if (valorRemovidoFila != valor) {
                    casosPosiveis.podeSerFila = 0;
                }
            }
        }

        limparFila(&fila);
        limparPilha(&pilha);

        if (casosPosiveis.podeSerFila == 1 && casosPosiveis.podeSerPilha == 1) {
            printf("indefinido\n");
        } else if (casosPosiveis.podeSerFila == 1) {
            printf("fila\n");
        } else if (casosPosiveis.podeSerPilha == 1) {
            printf("pilha\n");
        } else {
            printf("impossivel\n");
        }
    }

    return 0;
}

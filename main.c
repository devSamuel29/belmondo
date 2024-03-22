#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PRONTO,
    EXECUTANDO,
    ESPERANDO
} EstadoProcesso;

typedef struct {
    int id;
    int tempoChegada;
    int tempoExecucao;
    int tempoRestante;
    EstadoProcesso estado;
} Processo;

void adicionarProcesso(Processo *fila, int *tamanhoFila, Processo novoProcesso) {
    fila[*tamanhoFila] = novoProcesso;
    (*tamanhoFila)++;
}

void roundRobin(Processo *processos, int numProcessos, int quantum) {
    int tempoTotal = 0;
    int i, j;
    int tamanhoFila = 0;
    Processo fila[numProcessos];

    for (i = 0; i < numProcessos; i++) {
        processos[i].tempoRestante = processos[i].tempoExecucao;
        processos[i].estado = PRONTO;
    }

    i = 0;
    while (1) {
        int executou = 0;
        for (j = 0; j < numProcessos; j++) {
            if (processos[j].tempoChegada <= tempoTotal && processos[j].tempoRestante > 0) {
                processos[j].estado = EXECUTANDO;
                printf("Executando processo %d por 1 unidade de tempo\n", processos[j].id);
                processos[j].tempoRestante--;
                tempoTotal++;

                if (processos[j].tempoRestante == 0) {
                    printf("Processo %d concluÃ­do\n", processos[j].id);
                    processos[j].estado = PRONTO;
                } else {
                    processos[j].estado = ESPERANDO;
                    adicionarProcesso(fila, &tamanhoFila, processos[j]);
                }

                executou = 1;
                break;
            }
        }

        if (!executou) {
            tempoTotal++;
        }

        if (executou && quantum > 0) {
            if (fila[i].estado == ESPERANDO) {
                fila[i].estado = PRONTO;
            }
            adicionarProcesso(fila, &tamanhoFila, fila[i]);
        }

        if (i >= numProcessos && tamanhoFila == 0) {
            break;
        }

        if (executou && quantum > 0) {
            i = (i + 1) % numProcessos;
        }
    }
}

int main() {
    Processo processos[] = {
        {1, 0, 10, 0, PRONTO},
        {2, 0, 5, 0, PRONTO},
        {3, 0, 8, 0, PRONTO},
    };

    int numProcessos = sizeof(processos) / sizeof(processos[0]);
    int quantum = 2;

    roundRobin(processos, numProcessos, quantum);

    return 0;
}
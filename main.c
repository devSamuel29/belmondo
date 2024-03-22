#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSOS 30

typedef enum {
    PRONTO,
    EXECUTANDO,
    CONCLUIDO,
    BLOQUEADO
} Estado;

typedef struct {
    int id;
    int tempo_execucao;
    int tempo_restante;
    Estado estado;
} Processo;

void imprimir_estado(Processo *processos, int num_processos, int indice_processo_atual) {
    printf("Estado dos processos: ");
    for (int i = 0; i < num_processos; i++) {
        if (i == indice_processo_atual && processos[i].estado == EXECUTANDO) {
            printf("P%d:Em execução ", processos[i].id);
        } else if (processos[i].estado == PRONTO) {
            printf("P%d:Pronto ", processos[i].id);
        } else if (processos[i].estado == CONCLUIDO) {
            printf("P%d:Concluído ", processos[i].id);
        } else if (processos[i].estado == BLOQUEADO) {
            printf("P%d:Bloqueado ", processos[i].id);
        }
    }
    printf("\n");
}

void fila_round_robin(Processo *processos, int num_processos, int quantum) {
    int i, todos_processos_concluidos = 0;
    int tempo_total = 0;
    int indice_processo_atual = 0;

    while (!todos_processos_concluidos) {
        todos_processos_concluidos = 1;

        for (i = 0; i < num_processos; i++) {
            if (processos[i].estado == PRONTO) {
                todos_processos_concluidos = 0;

                int tempo_executado = quantum;
                if (processos[i].tempo_restante < quantum) {
                    tempo_executado = processos[i].tempo_restante;
                }

                processos[i].tempo_restante -= tempo_executado;
                tempo_total += tempo_executado;

                imprimir_estado(processos, num_processos, i);

                printf("Executando processo %d por %d unidades de tempo. ", processos[i].id, tempo_executado);
                if (processos[i].tempo_restante <= 0) {
                    processos[i].estado = CONCLUIDO;
                    printf("Processo %d concluído.\n", processos[i].id);
                } else {
                    processos[i].estado = BLOQUEADO;
                    printf("Processo %d bloqueado por 1 unidade de tempo.\n", processos[i].id);
                    i--;
                }

                break;
            }
        }
    }

    printf("\nTempo total de execução: %d unidades de tempo.\n", tempo_total);
}

int main() {
    int num_processos = 4; 
    int quantum = 2; 

    Processo processos[MAX_PROCESSOS] = {
        {1, 5, 5, PRONTO}, 
        {2, 3, 3, PRONTO},
        {3, 4, 4, PRONTO},
        {4, 2, 2, PRONTO}
    };

    fila_round_robin(processos, num_processos, quantum);

    return 0;
}
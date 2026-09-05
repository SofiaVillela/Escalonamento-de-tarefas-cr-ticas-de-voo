#ifndef FUNCOES_H
#define FUNCOES_H
#define MAX_TAM 100


typedef struct Tarefa{
    char nome[50];
    int periodo;
    int deadline;
    int burst;
}Tarefa;

int ler_file(FILE *file, int *tempo_total, Tarefa tarefas[], int *num_tarefas);
void execucao_rate();
void execucao_edf();
void imprimir_tarefas_teste(void);

#endif
#ifndef FUNCOES_H
#define FUNCOES_H
#define MAX_TAM 100


typedef struct Tarefa{
    char nome[50];
    int periodo;
    int deadline;
    int burst;
}Tarefa;

typedef struct {
    int restante;
    int proxima_chegada;
    int deadline_atual;
    int perdas;
    int concluidas;
} EstadoTarefa;

int ler_file(FILE *file, int *tempo_total, Tarefa tarefas[], int *num_tarefas);
void execucao_rate(int tempo_total, Tarefa tarefas[], int num_tarefas, EstadoTarefa estado[]);
void execucao_edf();
void imprimir_tarefas_teste(int tempo_total, Tarefa tarefas[], int num_tarefas);
void gravar_saida(const char *algoritmo, Tarefa tarefas[], EstadoTarefa estado[], int num_tarefas);

#endif
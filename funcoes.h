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
void imprimir_tarefas_teste(int tempo_total, Tarefa tarefas[], int num_tarefas);
void gravar_saida(const char *algoritmo, Tarefa tarefas[], EstadoTarefa estado[], int num_tarefas);
int escolher_rate(Tarefa tarefas[], EstadoTarefa estado[], int num_tarefas);
int escolher_edf( EstadoTarefa estado[], int num_tarefas);
void atualizar_estado(int t, Tarefa tarefas[], EstadoTarefa estado[], int num_tarefas);

#endif
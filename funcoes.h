#ifndef FUNCOES_H
#define FUNCOES_H


typedef struct Task{
    char *nome;
    int periodo;
    int deadline;
    int burst;
}Task;

void ler_file(FILE *file);
void execucao_rate();
void execucao_edf();

#endif
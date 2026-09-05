#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int ler_file(FILE *file, int *tempo_total, Tarefa tarefas[], int *num_tarefas){
    char linha[MAX_TAM];
    char *tokens[10];
    char *endptr;
    int primeira_linha = 1;

    while(fgets(linha, sizeof(linha), file) != NULL){
        size_t len = strlen(linha);
        if(len > 0 && linha[len - 1] == '\n'){
            linha[len - 1] = '\0';
        }

        tokens[0] = strtok(linha, " ");
        if(tokens[0] == NULL) continue;

        if(primeira_linha){
            *tempo_total = strtol(tokens[0], &endptr, 10);
            primeira_linha = 0;
            continue;
        }

        for(int i = 1; i <= 3; i++){
            tokens[i] = strtok(NULL, " ");
        }
        strcpy(tarefas[*num_tarefas].nome, tokens[0]);
        tarefas[*num_tarefas].periodo = strtol(tokens[1], &endptr, 10);
        tarefas[*num_tarefas].deadline = strtol(tokens[2], &endptr, 10);
        tarefas[*num_tarefas].burst = strtol(tokens[3], &endptr, 10);
        (*num_tarefas)++;

    }
    return 0;
}

void imprimir_tarefas_teste(void){
    printf("tempo_total: %d\n", tempo_total);
    for(int i = 0; i < num_tarefas; i++){
        printf("tarefa %d -> nome: %s, periodo: %d, deadline: %d, burst: %d\n",
               i, tarefas[i].nome, tarefas[i].periodo, tarefas[i].deadline, tarefas[i].burst);
    }
}

void execucao_rate(){

}

void execucao_edf(){

}
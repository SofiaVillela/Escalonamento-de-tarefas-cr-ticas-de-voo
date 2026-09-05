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
        if(*num_tarefas >= MAX_TAM){
            fprintf(stderr, "erro: max de tarefas atingido");
            return 1;
        }
        size_t len = strlen(linha);
        if(len > 0 && linha[len - 1] == '\n'){
            linha[len - 1] = '\0';
        }

        tokens[0] = strtok(linha, " ");
        if(tokens[0] == NULL) continue;

        if(primeira_linha){
            *tempo_total = strtol(tokens[0], &endptr, 10);
            if(endptr == tokens[0] || *endptr != '\0'){
                fprintf(stderr, "erro: valor nao numerico\n");
                return 1;
            }
            if(*tempo_total <= 0){
                fprintf(stderr, "erro: numero nao positivo\n");
                return 1;
            }
            primeira_linha = 0;
            continue;
        }

        for(int i = 1; i <= 3; i++){
            tokens[i] = strtok(NULL, " ");
            if(tokens[i] == NULL){
                fprintf(stderr, "erro: campo faltando\n");
                return 1;
            }
            
        }
        int valores[3];
        for(int i = 1; i <= 3; i++){
            valores[i - 1] = strtol(tokens[i], &endptr, 10);
            if(endptr == tokens[i] || *endptr != '\0'){
                fprintf(stderr, "erro: valor nao numerico\n");
                return 1;
            }
            if(valores[i - 1] <= 0){
                fprintf(stderr, "erro: numero nao positivo\n");
                return 1;
            }
        }

        if(valores[2] > valores[1] || valores[1] > valores[0] || valores[2] > valores[0]){
            fprintf(stderr, "erro: C <= D ≤<= P violado\n");
            return 1;
        }

        strcpy(tarefas[*num_tarefas].nome, tokens[0]);
        tarefas[*num_tarefas].periodo = valores[0];
        tarefas[*num_tarefas].deadline = valores[1];
        tarefas[*num_tarefas].burst = valores[2];
        (*num_tarefas)++;

    }
    if(primeira_linha == 1){
        fprintf(stderr, "erro: nenhuma linha valida");
        return 1;
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
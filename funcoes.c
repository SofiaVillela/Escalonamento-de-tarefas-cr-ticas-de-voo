#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int ler_file(FILE *file, int *tempo_total, Tarefa *tarefas, int *num_tarefas){
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
            fprintf(stderr, "erro: C <= D <= P violado\n");
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


void atualizar_estado(int t, Tarefa *tarefas, EstadoTarefa *estado, int num_tarefas, int *perda_em){
    for(int i = 0; i < num_tarefas; i++){
        if(t == estado[i].proxima_chegada){
            estado[i].restante = tarefas[i].burst;
            estado[i].deadline_atual = t + tarefas[i].deadline;
            estado[i].proxima_chegada += tarefas[i].periodo;
        }
        if(estado[i].restante > 0 && t == estado[i].deadline_atual){
            estado[i].perdas++;
            estado[i].restante = 0;
            perda_em[t] = i;
        }
    }
}

int escolher_rate(Tarefa *tarefas, EstadoTarefa *estado, int num_tarefas){
    int escolhida = -1;
    for(int i = 0; i < num_tarefas; i++){
        if(estado[i].restante > 0){
            if(escolhida == -1 || tarefas[i].periodo < tarefas[escolhida].periodo){
                escolhida = i;
            }
        }
    }
    return escolhida;
}

int escolher_edf(EstadoTarefa *estado, int num_tarefas){
    int escolhida = -1;
    for(int i = 0; i < num_tarefas; i++){
        if(estado[i].restante > 0){
            if(escolhida == -1 || estado[i].deadline_atual < estado[escolhida].deadline_atual){
                escolhida = i;
            }
        }
    }
    return escolhida;
}
void execucao_rate(int tempo_total, Tarefa *tarefas, int num_tarefas, EstadoTarefa *estado, int *rodou){
    int perda_em[tempo_total];
    for(int i = 0; i < num_tarefas; i++){
        estado[i].restante = 0;
        estado[i].proxima_chegada = 0;
        estado[i].deadline_atual = 0;
        estado[i].perdas = 0;
        estado[i].concluidas = 0;
    }
    for(int t = 0; t < tempo_total; t++){
        perda_em[t] = -1;
    }

    for(int t = 0; t < tempo_total; t++){
        atualizar_estado(t, tarefas, estado, num_tarefas, perda_em);
        int escolhida = escolher_rate(tarefas, estado, num_tarefas);
        executar(t, escolhida, estado, rodou);
    }
}

void execucao_edf(int tempo_total, Tarefa *tarefas, int num_tarefas, EstadoTarefa *estado, int *rodou){
    int perda_em[tempo_total];
    for(int i = 0; i < num_tarefas; i++){
        estado[i].restante = 0;
        estado[i].proxima_chegada = 0;
        estado[i].deadline_atual = 0;
        estado[i].perdas = 0;
        estado[i].concluidas = 0;
    }
    for(int t = 0; t < tempo_total; t++){
        perda_em[t] = -1;
    }

    for(int t = 0; t < tempo_total; t++){
        atualizar_estado(t, tarefas, estado, num_tarefas, perda_em);
        int escolhida = escolher_edf(estado, num_tarefas);
        executar(t, escolhida, estado, rodou);
    }
}

void gravar_saida(const char *algoritmo, Tarefa *tarefas, EstadoTarefa *estado, int num_tarefas, int *rodou, int tempo_total){
        char nome_file[30];
        sprintf(nome_file, "%s_svv.out", algoritmo);

        FILE *file_saida = fopen(nome_file, "w");
        if(file_saida == NULL){
            fprintf(stderr, "erro: nao foi possivel abrir o arquivo\n");
            return;
        }

        fprintf(file_saida, "EXECUTION BY %s\n", strcmp(algoritmo, "rate") == 0 ? "RATE" : "EDF");
        imprimir_execucao(file_saida, tarefas, rodou, tempo_total);
            fprintf(file_saida, "\nLOST DEADLINES\n");

        for(int i = 0; i < num_tarefas; i++){
            fprintf(file_saida, "[%s] %d\n", tarefas[i].nome, estado[i].perdas);
        }

        fprintf(file_saida, "\nCOMPLETE EXECUTION\n");
        for(int i = 0; i < num_tarefas; i++){
            fprintf(file_saida, "[%s] %d\n", tarefas[i].nome, estado[i].concluidas);
        }

        fprintf(file_saida, "\nKILLED\n");
        for(int i = 0; i < num_tarefas; i++){
            fprintf(file_saida, "[%s] %d\n", tarefas[i].nome, estado[i].restante > 0 ? 1 : 0);
        }

        fclose(file_saida);

}
void executar(int t, int escolhida, EstadoTarefa *estado, int *rodou){
    rodou[t] = escolhida;

    if(escolhida != -1){
        estado[escolhida].restante--;
        if(estado[escolhida].restante == 0){
            estado[escolhida].concluidas++;
        }
    }
}

void imprimir_execucao(FILE *file_saida, Tarefa tarefas[], int quem_rodou[], int tempo_total){
    int inicio = 0;
    while(inicio < tempo_total){
        int atual = quem_rodou[inicio];
        int fim = inicio;
        while(fim < tempo_total && quem_rodou[fim] == atual){
            fim++;
        }
        int duracao = fim - inicio;
        if(atual == -1){
            fprintf(file_saida, "idle for %d units\n", duracao);
        } else {
            fprintf(file_saida, "[%s] for %d units\n", tarefas[atual].nome, duracao);
        }
        inicio = fim;
    }
}
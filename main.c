#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(int argc, char **argv){
    
    if(argc != 3){
        fprintf(stderr,"erro: numero incorreto de argumentos\n");
        exit(1);
    }
    FILE *file = fopen(argv[2], "r");
    if(file == NULL){
        fprintf(stderr, "erro: nao foi possivel abrir o arquivo\n");
        exit(1);
    }
    int tempo_total;
    Tarefa tarefas[MAX_TAM];
    EstadoTarefa estado[MAX_TAM];
    int num_tarefas = 0;

    if(ler_file(file, &tempo_total, tarefas, &num_tarefas)!= 0){
        exit(1);
    }

    imprimir_tarefas_teste(tempo_total, tarefas, num_tarefas);

    Tarefa teste_tarefas[3];
    strcpy(teste_tarefas[0].nome, "A");
    teste_tarefas[0].periodo = 10;
    strcpy(teste_tarefas[1].nome, "B");
    teste_tarefas[1].periodo = 5;
    strcpy(teste_tarefas[2].nome, "C");
    teste_tarefas[2].periodo = 20;

    EstadoTarefa teste_estado[3];
    teste_estado[0].restante = 3;  
    teste_estado[1].restante = 0; 
    teste_estado[2].restante = 5;  

    int resultado = escolher_rate(teste_tarefas, teste_estado, 3);
    printf("escolhida: %d (esperado: 0)\n", resultado);
    if(strcmp(argv[1], "rate") == 0){
        
        gravar_saida("rate", tarefas, estado, num_tarefas);
    }
    else if(strcmp(argv[1], "edf") == 0){
       
    }
    else{
        fprintf(stderr, "erro: algoritmo invalido\n");
        exit(1);
    }
    

    fclose(file);
    return 0;
}
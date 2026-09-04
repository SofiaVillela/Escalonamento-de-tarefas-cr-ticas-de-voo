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
    ler_file(file);

    if(strcmp(argv[1], "rate") == 0){
        execucao_rate();
    }
    else if(strcmp(argv[1], "edf") == 0){
        execucao_edf();
    }
    else{
        fprintf(stderr, "erro: algoritmo invalido\n");
        exit(1);
    }
    

    fclose(file);
    return 0;
}
# Escalonamento de Tarefas Críticas de Voo
 
Simulador de escalonamento de tarefas periódicas de tempo real, implementando os algoritmos rate-monotonic e earliest-deadline-first.
 
## Arquivos
 
- `main.c`: lê os argumentos da linha de comando, abre o arquivo de tarefas, chama a leitura (`ler_file`), executa o algoritmo escolhido (`execucao_rate` ou `execucao_edf`) e grava a saída (`gravar_saida`).
- `funcoes.c`: implementa a leitura e validação do arquivo de entrada, a simulação dos dois algoritmos de escalonamento e a geração do arquivo de saída.
- `funcoes.h`: declara as structs `Tarefa` e `EstadoTarefa` e os protótipos de todas as funções.
- `Makefile`: compila o projeto.

## Como compilar
 make

 
 
## Como executar
./scheduler <rate|edf> <arquivo_de_tarefas>

 
Exemplo:
./scheduler rate voo.txt

 
A saída é gravada em `rate_svv.out` ou `edf_svv.out`, dependendo do algoritmo escolhido. O programa nunca escreve a saída da simulação na tela — só em caso de erro, e nesse caso a mensagem vai para stderr, o programa termina com código de saída diferente de zero, e nenhum arquivo de saída é criado.
 
## Formato do arquivo de entrada
 
Primeira linha: tempo total de simulação (inteiro positivo).
 
Linhas seguintes, uma por tarefa: `nome periodo deadline burst`, com a obrigação `burst <= deadline <= periodo`.
 

## Sistema operacional
 
Desenvolvido em WSL (Windows Subsystem for Linux) sobre Windows.
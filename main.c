
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//incluindo contratos dos outros membros
#include "fila_fifo.h"
#include "logtree.h"
#include "escalonador.h"

int main(int argc, char *argv[]) {
    //verificando argumentos de linha de comando
    if (argc < 2) {
        printf("Uso: %s <numero_do_teste>\n", argv[0]);
        printf("Exemplo: %s 0001\n", argv[0]);
        return 1;
    }

    //formatando nomes de arquivo
    char nomeEntrada[50];
    char nomeSaida[50];
    
    // transforma (ex: 1) em "entrada-0001.txt"
    int idTeste = atoi(argv[1]);
    sprintf(nomeEntrada, "entrada-%04d.txt", idTeste);
    sprintf(nomeSaida, "saida-%04d.txt", idTeste);

    // estruturas padrão PascalCase
    Escalonador meuBanco;
    
    //implementar EConfPorArquivo para ler M, DeltaT e Ni
    if (EConfPorArquivo(&meuBanco, nomeEntrada) != 0) {
        fprintf(stderr, "Erro ao abrir ou ler o arquivo de configuracao: %s\n", nomeEntrada);
        return 1;
    }

    // execução da simulação
    printf("Iniciando simulacao para o teste: %04d\n", idTeste);
    ERodar(&meuBanco, nomeEntrada, nomeSaida);

    printf("Simulacao concluida. Resultado em: %s\n", nomeSaida);

    return 0;
}
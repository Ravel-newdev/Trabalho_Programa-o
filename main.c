#include <stdio.h>
#include <stdlib.h>

#include "escalonador.h"

int main(int argc, char *argv[])
{
    Escalonador *meuBanco = (Escalonador *)malloc(sizeof(Escalonador));
    char nomeEntrada[50];
    char nomeSaida[50];
    int idTeste;
    
    // verificando argumentos de linha de comando
    if (argc < 2) {
        printf("Número de argumentos inválido.\n");
        printf("Veja alguns exemplos de como você poderia usar:\n");
        printf("%s 0001\n", argv[0]);
        printf("%s 1\n", argv[0]);
        return EXIT_FAILURE;
    }

    idTeste = atoi(argv[1]);

    // ex: transforma o 1 de idTeste em "entrada-0001.txt"
    sprintf(nomeEntrada, "entradas/entrada-%04d.txt", idTeste);
    sprintf(nomeSaida, "resultados/saida-%04d.txt", idTeste);
    
    ERodar(meuBanco, nomeEntrada, nomeSaida);

    return 1;
}
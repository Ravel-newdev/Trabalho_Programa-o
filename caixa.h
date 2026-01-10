#ifndef CAIXA_H
#define CAIXA_H 

#include "escalonador.h"
#include "fila_fifo.h"

typedef struct {
    int livre;
    int tempoRestante;
    int conta;
} Caixa;

void atualizaTempoCaixas(Caixa *caixas, int M);
int pegaCaixaLivre(Caixa *caixas, int M);
int existemCaixasOcupados(Caixa *caixas, int M);
void rodadaAtendimento(Escalonador *esc, Caixa *caixas);

#endif
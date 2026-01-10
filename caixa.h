#ifndef CAIXA_H
#define CAIXA_H 

#include "escalonador.h"
#include "fila_fifo.h"
#include "logtree.h"
#include <stdio.h>

typedef struct {
    int livre;
    int tempoRestante;
    int conta;
} Caixa;

void atualiza_tempo_caixas(Caixa *caixas, int M);
int pega_caixa_livre(Caixa *caixas, int M);
int existem_caixas_ocupados(Caixa *caixas, int M);
void rodada_atendimento(Escalonador *esc, Caixa *caixas, Log **raiz_log, int tempo_atual, FILE *out);

#endif
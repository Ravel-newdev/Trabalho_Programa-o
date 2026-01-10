#ifndef LONGTREE_H
#define LONGTREE_H

#include <stdio.h>

typedef struct log {
    int conta;
    int classe;
    int tempo;
    int caixa;
    int operacoes;
    struct log *esq;
    struct log *dir;
} Log;

void log_inicializar(Log **l);
void log_registrar(Log **l, int conta, int classe, int tempo, int caixa, int operacoes);
int log_obter_soma_por_classe(Log **l, int classe);
int log_obter_contagem_por_classe(Log **l, int classe);
int log_obter_soma_ops_por_classe(Log **l, int classe);
float log_media_por_classe(Log **l, int classe);
float log_media_ops_por_classe(Log **l, int classe);
int log_total_por_caixa(Log **l, int num_caixa);
void log_gerar_relatorio(Log **l, int tempo_total, int qtd_caixas, FILE *out);

void log_liberar(Log *l);

#endif

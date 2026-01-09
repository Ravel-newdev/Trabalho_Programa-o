#ifndef LONGTREE_H
#define LONGTREE_H

typedef struct log {
    int conta;
    int classe;
    int tempo;
    int caixa;
    struct log *esq;
    struct log *dir;
} Log;

void log_inicializar(Log **l);
void log_registrar(Log **l, int conta, int classe, int tempo, int caixa);
int  log_obter_soma_por_classe(Log **l, int classe);
int  log_obter_contagem_por_classe(Log **l, int classe);
float log_media_por_classe(Log **l, int classe);
void log_liberar(Log *l);

#endif

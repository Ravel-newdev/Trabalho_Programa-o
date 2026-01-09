#include <stdio.h>
#include <stdlib.h>
#include "logtree.h"

typedef struct log {
    int valor;
    int classe;
    int tempo;
    int caixa;

    struct log *esq;
    struct log *dir;
} Log;

void inicializar(Log **l) {
    *l = NULL;
}

Log* criar_no(int conta, int classe, int tempo, int caixa) {
    Log *novo = malloc(sizeof(Log));

    if (novo == NULL) return NULL;

    novo->conta = conta;
    novo->classe = classe;
    novo->tempo = tempo;
    novo->caixa = caixa;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

void log_registrar(Log **l, int conta, int classe, int tempo, int caixa) {
    if (*l == NULL) {
        *l = criar_no(conta, classe, tempo, caixa);
        return;
    }

    if (classe < (*l)->classe) {
        log_registrar(&(*l)->esq, conta, classe, tempo, caixa);
    } else {
        log_registrar(&(*l)->dir, conta, classe, tempo, caixa);
    }
}

int log_obter_soma_por_classe(Log **l, int classe) {
    if (*l == NULL) return 0;

    int soma = 0;

    if ((*l)->classe == classe) {
        soma += (*l)->tempo;
    }

    soma += log_obter_soma_por_classe(&(*l)->esq, classe);
    soma += log_obter_soma_por_classe(&(*l)->dir, classe);

    return soma;
}

int log_obter_contagem_por_classe(Log **l, int classe) {
    if (*l == NULL) return 0;

    int cont = 0;

    if ((*l)->classe == classe) {
        cont = 1;
    }

    cont += log_obter_contagem_por_classe(&(*l)->esq, classe);
    cont += log_obter_contagem_por_classe(&(*l)->dir, classe);

    return cont;
}

float log_media_por_classe(Log **l, int classe) {
    int soma = log_obter_soma_por_classe(l, classe);
    int qtd  = log_obter_contagem_por_classe(l, classe);

    if (qtd == 0) return 0.0;

    return (float) soma / qtd;
}

void log_liberar(Log *l) {
    if (l == NULL) return;

    log_liberar(l->esq);
    log_liberar(l->dir);

    free(l);
}

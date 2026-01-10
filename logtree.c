#include <stdlib.h>
#include <stdio.h>
#include "logtree.h"

void log_inicializar(Log **l) {
    *l = NULL;
}

Log* criar_no(int conta, int classe, int tempo, int caixa, int operacoes) {
    Log *novo = malloc(sizeof(Log));

    if (novo == NULL) return NULL;

    novo->conta = conta;
    novo->classe = classe;
    novo->tempo = tempo;
    novo->caixa = caixa;
    novo->operacoes = operacoes;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

void log_registrar(Log **l, int conta, int classe, int tempo, int caixa, int operacoes) {
    if (*l == NULL) {
        *l = criar_no(conta, classe, tempo, caixa, operacoes);
        return;
    }

    if (conta < (*l)->conta) {
        log_registrar(&(*l)->esq, conta, classe, tempo, caixa, operacoes);
    } else {
        log_registrar(&(*l)->dir, conta, classe, tempo, caixa, operacoes);
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

int log_obter_soma_ops_por_classe(Log **l, int classe) {
    if (*l == NULL) return 0;

    int soma = 0;

    if ((*l)->classe == classe) {
        soma += (*l)->operacoes;
    }

    soma += log_obter_soma_ops_por_classe(&(*l)->esq, classe);
    soma += log_obter_soma_ops_por_classe(&(*l)->dir, classe);

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

float log_media_ops_por_classe(Log **l, int classe)
{
    int soma = log_obter_soma_ops_por_classe(l, classe);
    int qtd  = log_obter_contagem_por_classe(l, classe);

    if (qtd == 0) return 0.0;

    return (float) soma / qtd;
}

// --- Função para contar atendimentos por Caixa ---
int log_total_por_caixa(Log **l, int num_caixa) 
{
    int conta;
    if (*l == NULL) return 0;
    
    conta = ((*l)->caixa == num_caixa) ? 1 : 0;

    conta += log_total_por_caixa(&(*l)->esq, num_caixa);
    conta += log_total_por_caixa(&(*l)->dir, num_caixa);

    return conta;
}

// estatíscicas gerais do dia de atendimento
void log_gerar_relatorio(Log **l, int tempo_total, int qtd_caixas, FILE *out)
{
    char *nomes[] = {"Premium", "Ouro", "Prata", "Bronze", "Comuns"}; // Leezu = Comuns no log
    char *nomes_ops[] = {"Premium", "Ouro", "Prata", "Bronze", "Leezu"};
    int i, qtd, total;
    float media, media_ops;

    fprintf(out, "Tempo total de atendimento: %d minutos.\n", tempo_total);

    // médias de espera
    for (i = 0; i < 5; i++) {
        qtd = log_obter_contagem_por_classe(l, i);
        media = log_media_por_classe(l, i);
        fprintf(out, "Tempo medio de espera dos %d clientes %s: %.2f\n", qtd, nomes[i], media);
    }

    // médias de operações
    for (i = 0; i < 5; i++) {
        media_ops = log_media_ops_por_classe(l, i);
        fprintf(out, "Quantidade media de operacoes por cliente %s = %.2f\n", nomes_ops[i], media_ops);
    }

    // contagem por caixa
    for (i = 1; i <= qtd_caixas; i++) {
        total = log_total_por_caixa(l, i);
        fprintf(out, "O caixa de número %d atendeu %d clientes.\n", i, total);
    }
}

void log_liberar(Log *l) {
    if (l == NULL) return;

    log_liberar(l->esq);
    log_liberar(l->dir);

    free(l);
}

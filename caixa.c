#include <stdio.h>
#include "caixa.h"
#include "escalonador.h"
#include "logtree.h"

void atualiza_tempo_caixas(Caixa *caixas, int M)
{
    int i;
    for (i = 0; i < M; i++) {
        if (!caixas[i].livre) {
            caixas[i].tempoRestante--;

            if (caixas[i].tempoRestante <= 0) {
                caixas[i].livre = 1;
                caixas[i].conta = -1;
            }
        }
    }
}

int pega_caixa_livre(Caixa *caixas, int M)
{
    int i;
    for (i = 0; i < M; i++) {
        if (caixas[i].livre) return i;
    }
    return -1;
}

int existem_caixas_ocupados(Caixa *caixas, int M)
{
    int i;
    for (i = 0; i < M; i++) {
        if (!caixas[i].livre) {
            return 1;
        }
    }
    return 0;
}

void rodada_atendimento(Escalonador *e, Caixa *caixas, Log **raiz_log, int tempo_atual, FILE *out)
{
    int idx_caixa, ops_cliente, conta_cliente, classe_cliente;

    char *nomes_cat[] = {"Premium", "Ouro", "Prata", "Bronze", "Leezu"};
    
    while (1) {
        idx_caixa = pega_caixa_livre(caixas, e->qtd_caixas);
        if (idx_caixa == -1) return; 

        conta_cliente = e_obter_prox_cliente(e, &ops_cliente, &classe_cliente);

        // acabaram os clientes
        if (conta_cliente == -1) return;

        caixas[idx_caixa].livre = 0;
        caixas[idx_caixa].conta = conta_cliente;
        caixas[idx_caixa].tempoRestante = ops_cliente * e->delta_t;

        fprintf(out, "T = %d min: Caixa %d chama da categoria %s cliente da conta %d para realizar %d operacao(oes).\n", 
               tempo_atual, 
               idx_caixa + 1,
               nomes_cat[classe_cliente],
               conta_cliente,
               ops_cliente);

        log_registrar(raiz_log, conta_cliente, classe_cliente, tempo_atual, idx_caixa + 1, ops_cliente);
    }
}

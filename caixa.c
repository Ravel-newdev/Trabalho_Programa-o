#include "caixa.h"
#include "escalonador.h"

void atualizaTempoCaixas(Caixa *caixas, int M)
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

int pegaCaixaLivre(Caixa *caixas, int M)
{
    int i;
    for (i = 0; i < M; i++) {
        if (caixas[i].livre) return i;
    }
    return -1;
}

int existemCaixasOcupados(Caixa *caixas, int M)
{
    int i;
    for (i = 0; i < M; i++) {
        if (!caixas[i].livre) {
            return 1;
        }
    }
    return 0;
}

void rodadaAtendimento(Escalonador *esc, Caixa *caixas)
{
    int idx_caixa, ops_cliente, conta_cliente;
    
    while (1) {
        idx_caixa = pegaCaixaLivre(caixas, esc->qtd_caixas);
        if (idx_caixa == -1) return; 

        conta_cliente = EPegarProxCliente(esc, &ops_cliente);

        // acabaram os clientes
        if (conta_cliente == -1) return;

        caixas[idx_caixa].livre = 0;
        caixas[idx_caixa].conta = conta_cliente;
        caixas[idx_caixa].tempoRestante = ops_cliente * esc->delta_t;
    }
}

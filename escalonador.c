#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escalonador.h"
#include "fila_fifo.h"
#include "caixa.h"

void EInicializar(Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5)
{
    Fila_FIFO *Premium, *Ouro, *Prata, *Bronze, *Leezu;
    FInicializar(&Premium);
    FInicializar(&Ouro);
    FInicializar(&Prata);
    FInicializar(&Bronze);
    FInicializar(&Leezu);

    e->filas[0] = Premium;
    e->filas[1] = Ouro;
    e->filas[2] = Prata;
    e->filas[3] = Bronze;
    e->filas[4] = Leezu;

    e->n[0] = n_1;
    e->n[1] = n_2;
    e->n[2] = n_3;
    e->n[3] = n_4;
    e->n[4] = n_5;
    
    e->qtd_caixas = caixas;
    e->delta_t = delta_t;
    e->fila_atual = 0;
    e->atendidos_na_fila = 0;
}

int EConfPorArquivo(Escalonador *e, char *nome_arq_conf)
{
    char linha[100];
    int caixas, delta_t, n_1, n_2, n_3, n_4, n_5;
    char classe[20];
    int conta, operacoes;
    FILE *arq_conf = fopen(nome_arq_conf, "r");

    if (arq_conf == NULL) {
        return 0;
    }

    /* Leitura das configurações do arquivo */
    /* TODO: verificar retorno de sscanf */
    fgets(linha, sizeof(linha), arq_conf);
    sscanf(linha, "qtde de caixas = %d", &caixas);

    fgets(linha, sizeof(linha), arq_conf);
    sscanf(linha, "delta t = %d", &delta_t);

    fgets(linha, sizeof(linha), arq_conf);
    sscanf(linha, "disciplina de escalonamento = {%d,%d,%d,%d,%d}", &n_1,&n_2,&n_3,&n_4,&n_5);

    EInicializar(e, caixas, delta_t, n_1, n_2, n_3, n_4, n_5);

    /* Leitura das entradas de clientes */
    while (fgets(linha, sizeof(linha), arq_conf)) {
        sscanf(linha, "%s - conta %d - %d operacao(oes)", classe, &conta, &operacoes);

        if (strcmp(classe, "Premium") == 0) {
            EInserirPorFila(e, 0, conta, operacoes);
        } else if (strcmp(classe, "Ouro") == 0) {
            EInserirPorFila(e, 1, conta, operacoes);
        } else if (strcmp(classe, "Prata") == 0) {
            EInserirPorFila(e, 2, conta, operacoes);
        } else if (strcmp(classe, "Bronze") == 0) {
            EInserirPorFila(e, 3, conta, operacoes);
        } else if (strcmp(classe, "Leezu") == 0) {
            EInserirPorFila(e, 4, conta, operacoes);
        }
    }

    fclose(arq_conf);
    return 1;
}

int EInserirPorFila(Escalonador *e, int classe, int num_conta, int qtde_operacoes)
{
    if (classe < 0 || classe > 4) {
        return 0;
    }
    return FInserir(&e->filas[classe], num_conta, qtde_operacoes);
}

int EVerQtdeClientes(Escalonador *e)
{
    int total = 0;
    for (int i = 0; i < 5; i++) {
        total += FNumElementos(&e->filas[i]);
    }
    return total;
}

int EPegarProxNumConta(Escalonador *e) 
{
    int limite, fila;

    while (1) {
        fila = e->fila_atual;
        limite = e->n[fila];

        if (e->atendidos_na_fila < limite && FNumElementos(&e->filas[fila]) > 0)
        {
            e->atendidos_na_fila++;
            return FPegaProximaChave(&e->filas[fila]);
        }

        e->fila_atual = (e->fila_atual + 1) % 5;
        e->atendidos_na_fila = 0;

        if (FNumElementos(&e->filas[0]) == 0 &&
            FNumElementos(&e->filas[1]) == 0 &&
            FNumElementos(&e->filas[2]) == 0 &&
            FNumElementos(&e->filas[3]) == 0 &&
            FNumElementos(&e->filas[4]) == 0)
        {
            return -1;
        }
    }
}

int EVerProxNumConta(Escalonador *e)
{
    int limite, fila;

    while (1) {
        fila = e->fila_atual;
        limite = e->n[fila];

        if (e->atendidos_na_fila < limite && FNumElementos(&e->filas[fila]) > 0)
        {
            e->atendidos_na_fila++;
            return FVerProximaChave(&e->filas[fila]);
        }

        e->fila_atual = (e->fila_atual + 1) % 5;
        e->atendidos_na_fila = 0;

        if (FNumElementos(&e->filas[0]) == 0 &&
            FNumElementos(&e->filas[1]) == 0 &&
            FNumElementos(&e->filas[2]) == 0 &&
            FNumElementos(&e->filas[3]) == 0 &&
            FNumElementos(&e->filas[4]) == 0)
        {
            return -1;
        }
    }
}

int EVerProxQtdeOper(Escalonador *e)
{
    int limite, fila;

    while (1) {
        fila = e->fila_atual;
        limite = e->n[fila];

        if (e->atendidos_na_fila < limite && FNumElementos(&e->filas[fila]) > 0)
        {
            e->atendidos_na_fila++;
            return FVerProximoValor(&e->filas[fila]);
        }

        e->fila_atual = (e->fila_atual + 1) % 5;
        e->atendidos_na_fila = 0;

        if (FNumElementos(&e->filas[0]) == 0 &&
            FNumElementos(&e->filas[1]) == 0 &&
            FNumElementos(&e->filas[2]) == 0 &&
            FNumElementos(&e->filas[3]) == 0 &&
            FNumElementos(&e->filas[4]) == 0)
        {
            return -1;
        }
    }
}

int EVerProxFila(Escalonador *e)
{
    return (e->fila_atual + 1) % 5;
}

int EVerTempoProxCliente(Escalonador *e)
{
    return e->delta_t * EVerProxQtdeOper(e);
}

/* Retorna a conta do cliente a ser atendido e passa por
 * referência a quantidade de operações em *qtd_ops
 */
int EPegarProxCliente(Escalonador *e, int *qtd_ops) 
{
    int limite, fila, conta;

    // todas as filas vazias
    if (FNumElementos(&e->filas[0]) == 0 &&
        FNumElementos(&e->filas[1]) == 0 &&
        FNumElementos(&e->filas[2]) == 0 &&
        FNumElementos(&e->filas[3]) == 0 &&
        FNumElementos(&e->filas[4]) == 0) 
    {
        return -1;
    }

    while (1) {
        fila = e->fila_atual;
        limite = e->n[fila];

        if (e->atendidos_na_fila < limite && FNumElementos(&e->filas[fila]) > 0)
        {
            *qtd_ops = FVerProximoValor(&e->filas[fila]); 
            conta = FPegaProximaChave(&e->filas[fila]);

            e->atendidos_na_fila++;
            
            return conta;
        }

        e->fila_atual = (e->fila_atual + 1) % 5;
        e->atendidos_na_fila = 0;
    }
}

void ERodar(Escalonador *e, char *nome_arq_in, char *nome_arq_out)
{
    Caixa *caixas;
    int tempo = 0;
    int M;
    
    EConfPorArquivo(e, nome_arq_in);

    M = e->qtd_caixas;
    caixas = (Caixa *)malloc(M * sizeof(Caixa));

    for (int i = 0; i < M; i++) {
        caixas[i].livre = 1;
        caixas[i].tempoRestante = 0;
        caixas[i].conta = -1;
    }

    while (EVerQtdeClientes(e) > 0 || existemCaixasOcupados(caixas, M)) {
        if (tempo > 0) {
            atualizaTempoCaixas(caixas, M);
        }

        rodadaAtendimento(e, caixas);

        tempo++;
    }

    free(caixas);
    printf("Simulacao concluida. Tempo total: %d minutos.\n", tempo - 1);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "escalonador.h"
#include "fila_fifo.h"
#include "caixa.h"
#include "logtree.h"

void e_inicializar(Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5)
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

int e_conf_por_arquivo(Escalonador *e, char *nome_arq_conf)
{
    char linha[100];
    int caixas, delta_t, n_1, n_2, n_3, n_4, n_5;
    char classe[20];
    int conta, operacoes;
    FILE *arq_conf = fopen(nome_arq_conf, "r");

    if (arq_conf == NULL) {
        printf("Arquivo não encontrado!\n");
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

    e_inicializar(e, caixas, delta_t, n_1, n_2, n_3, n_4, n_5);

    /* Leitura das entradas de clientes */
    while (fgets(linha, sizeof(linha), arq_conf)) {
        sscanf(linha, "%s - conta %d - %d operacao(oes)", classe, &conta, &operacoes);

        if (strcmp(classe, "Premium") == 0) {
            e_inserir_por_fila(e, 0, conta, operacoes);
        } else if (strcmp(classe, "Ouro") == 0) {
            e_inserir_por_fila(e, 1, conta, operacoes);
        } else if (strcmp(classe, "Prata") == 0) {
            e_inserir_por_fila(e, 2, conta, operacoes);
        } else if (strcmp(classe, "Bronze") == 0) {
            e_inserir_por_fila(e, 3, conta, operacoes);
        } else if (strcmp(classe, "Leezu") == 0) {
            e_inserir_por_fila(e, 4, conta, operacoes);
        }
    }

    fclose(arq_conf);
    return 1;
}

int e_inserir_por_fila(Escalonador *e, int classe, int num_conta, int qtde_operacoes)
{
    if (classe < 0 || classe > 4) {
        return 0;
    }
    return FInserir(&e->filas[classe], num_conta, qtde_operacoes);
}

int e_consultar_qtde_clientes(Escalonador *e)
{
    int total = 0;
    int i;
    for (i = 0; i < 5; i++) {
        total += FNumElementos(&e->filas[i]);
    }
    return total;
}

int e_consultar_prox_num_conta(Escalonador *e)
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

int e_obter_prox_num_conta(Escalonador *e) 
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

int e_consultar_prox_qtde_oper(Escalonador *e)
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

int e_ver_prox_fila(Escalonador *e)
{
    return (e->fila_atual + 1) % 5;
}

int e_consultar_tempo_prox_cliente(Escalonador *e)
{
    if (e_consultar_prox_qtde_oper(e) == -1) {
        return -1;
    }

    return e->delta_t * e_consultar_prox_qtde_oper(e);
}

/* Retorna a conta do cliente a ser atendido e passa por
 * referência a quantidade de operações e a classe do cliente.
 */
int e_obter_prox_cliente(Escalonador *e, int *qtd_ops, int *classe_cliente)
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
            *classe_cliente = fila;
            *qtd_ops = FVerProximoValor(&e->filas[fila]);
            conta = FPegaProximaChave(&e->filas[fila]);

            e->atendidos_na_fila++;
            
            return conta;
        }

        e->fila_atual = (e->fila_atual + 1) % 5;
        e->atendidos_na_fila = 0;
    }
}

void e_rodar(Escalonador *e, char *nome_arq_in, char *nome_arq_out)
{
    Caixa *caixas;
    Log *raiz_log;
    FILE *arq_saida = fopen(nome_arq_out, "w");
    int tempo = 0;
    int M;
    int simulacao_ativa = 1;

    if (arq_saida == NULL) {
        printf("Erro ao criar arquivo de saida!\n");
        return;
    }
    
    e_conf_por_arquivo(e, nome_arq_in);
    log_inicializar(&raiz_log);

    M = e->qtd_caixas;
    caixas = (Caixa *)malloc(M * sizeof(Caixa));

    for (int i = 0; i < M; i++) {
        caixas[i].livre = 1;
        caixas[i].tempoRestante = 0;
        caixas[i].conta = -1;
    }

    while (simulacao_ativa) {
        if (tempo > 0) {
            atualiza_tempo_caixas(caixas, M);
        }

        if (e_consultar_qtde_clientes(e) == 0 && !existem_caixas_ocupados(caixas, M)) {
            simulacao_ativa = 0;
        }

        rodada_atendimento(e, caixas, &raiz_log, tempo, arq_saida);
        tempo++;
    }

    log_gerar_relatorio(&raiz_log, tempo - 1, e->qtd_caixas, arq_saida);
    fclose(arq_saida);

    printf("Simulacao concluida. Tempo total: %d minutos.\n", tempo - 1);

    log_liberar(raiz_log);
    free(caixas);
}

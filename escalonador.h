#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "fila_fifo.h"

typedef struct {
    Fila_FIFO *filas[5];
    int n[5]; // disciplina de atendimento
    int qtd_caixas;
    int delta_t;
    int fila_atual;
    int atendidos_na_fila;
} Escalonador;

void e_inicializar(Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5);
int e_inserir_por_fila(Escalonador *e, int classe, int num_conta, int qtde_operacoes);
int e_obter_prox_num_conta(Escalonador *e);
int e_consultar_prox_num_conta(Escalonador *e);
int e_ver_prox_qtde_operacoes(Escalonador *e);
int e_ver_prox_fila(Escalonador *e);
int e_consultar_qtde_clientes(Escalonador *e);
int e_consultar_tempo_prox_cliente(Escalonador *e);
int e_obter_prox_cliente(Escalonador *e, int *qtd_ops, int *classe_cliente);
int e_conf_por_arquivo(Escalonador *e, char *nome_arq_conf);
void e_rodar(Escalonador *e, char *nome_arq_in, char *nome_arq_out);

#endif
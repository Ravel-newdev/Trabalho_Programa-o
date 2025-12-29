

#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "fila_fifo.h"

typedef struct {
    Fila_FIFO *filas[5]; 
    int n[5];            
    int qtd_caixas;      
    int delta_t;         
} Escalonador;

void EInicializar(Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5);
int EInserirPorFila(Escalonador *e, int classe, int num_conta, int qtde_operacoes);
int EPegaProxNumConta(Escalonador *e);         
int EVerProxNumConta(Escalonador *e);          
int EVerProxQtdeOper(Escalonador *e);          
int EVerProxFila(Escalonador *e);              
int EVerQtdeClientes(Escalonador *e);          
int EVerTempoProxCliente(Escalonador *e);      
int EConfPorArquivo(Escalonador *e, char *nome_arq_conf);
void ERodar(Escalonador *e, char *nome_arq_in, char *nome_arq_out);

#endif


#ifndef FILA_FIFO_H
#define FILA_FIFO_H

typedef struct no {
    int chave; 
    int valor; 
    struct no *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila_FIFO;

void FInicializar(Fila_FIFO **refFila);
int FInserir(Fila_FIFO **refFila, int chave, int valor);
int FPegaProximaChave(Fila_FIFO **refFila);        
int FVerProximaChave(Fila_FIFO **refFila);         
int FVerProximoValor(Fila_FIFO **refFila);         
int FNumElementos(Fila_FIFO **refFila);
int FVerChavePorPosicao(Fila_FIFO **refFila, int posicao); 
int FVerValorPorPosicao(Fila_FIFO **refFila, int posicao); 

#endif
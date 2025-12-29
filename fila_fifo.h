

#ifndef FILA_FIFO_H
#define FILA_FIFO_H

typedef struct no {
    int chave; 
    int valor; 
    struct no *proximo;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila_FIFO;

void FInicializar(Fila_FIFO **f);
int FInserir(Fila_FIFO **f, int chave, int valor);
int FPegaProximaChave(Fila_FIFO **f);        
int FVerProximaChave(Fila_FIFO **f);         
int FVerProximoValor(Fila_FIFO **f);         
int FNumElementos(Fila_FIFO **f);
int FVerChavePorPosicao(Fila_FIFO **f, int posicao); 
int FVerValorPorPosicao(Fila_FIFO **f, int posicao); 

#endif
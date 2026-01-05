#include <stdio.h>
#include <stdlib.h>
#include "fila_fifo.h"

/*  a estrutura */
void FInicializar(Fila_FIFO **refFila) {
    *refFila = (Fila_FIFO *)malloc(sizeof(Fila_FIFO));
    if (*refFila != NULL) {
        (*refFila)->inicio = NULL;
        (*refFila)->fim = NULL;
    }
}


/* aqui inserimos um novo cliente na fila garantindo que a chave seja unica */
int FInserir(Fila_FIFO **refFila, int chave, int valor) {
    if (refFila == NULL || *refFila == NULL) {
        return 0;
    }

    /* verificando chave unica */ 
    No *NOatual = (*refFila)->inicio;
    while (NOatual != NULL) {
        if (NOatual->chave == chave) {
            return 0; //aqui a chave duplicada encontrada não sera inserida
        }
        NOatual = NOatual->prox;
    }

    /* o novo nó */
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) return 0; //se falha de memória

    novo->chave = chave;
    novo->valor = valor;
    novo->prox = NULL;

    /* aqui inserimos no fim da fila FIFO */
    if ((*refFila)->inicio == NULL) {
        (*refFila)->inicio = novo;
    } else {
        (*refFila)->fim->prox = novo;
    }
    (*refFila)->fim = novo;

    return 1; 
}

/* remove e retorna a chave do primeiro elemento */
int FPegaProximaChave(Fila_FIFO **refFila) {
    if (refFila == NULL || *refFila == NULL || (*refFila)->inicio == NULL) {
        return -1;
    }

    No *tempRemocao = (*refFila)->inicio;
    int chave = tempRemocao->chave;

    (*refFila)->inicio = tempRemocao->prox;

    if ((*refFila)->inicio == NULL) {
        (*refFila)->fim = NULL;
    }

    free(tempRemocao);
    return chave;
}

/*verifico a chave do primeiro sem remover */
int FVerProximaChave(Fila_FIFO **refFila) {
    if (refFila == NULL || *refFila == NULL || (*refFila)->inicio == NULL) {
        return -1;
    }

    return (*refFila)->inicio->chave;
}

/*consulto o value do primeiro sem remover */
int FVerProximoValor(Fila_FIFO **refFila) {
    if (refFila == NULL || *refFila == NULL || (*refFila)->inicio == NULL) {
        return -1;
    }
    return (*refFila)->inicio->valor;
}


/* retorna o total de nós na fila */
int FNumElementos(Fila_FIFO **refFila) {
    if (refFila == NULL || *refFila == NULL) {
        return 0;
    }

    int total = 0;

    No *Ptaux = (*refFila)->inicio;
    while (Ptaux != NULL) {
        total++;
        Ptaux = Ptaux->prox;
    }

    return total;
}

/* consigo identificar chave em posição específica onde 0 é o início */
int FVerChavePorPosicao(Fila_FIFO **refFila, int posicao) {
    if (refFila == NULL || *refFila == NULL) {
        return -1;
    }

    No *atual = (*refFila)->inicio;

    int i = 0;
    while (atual != NULL) {
        if (i == posicao) {
            return atual->chave;
        }

        atual = atual->prox;
        i++;
    }
    return -1;
}

/*vejo o valor em posição específica */
int FVerValorPorPosicao(Fila_FIFO **refFila, int posicao) {
    if (refFila == NULL || *refFila == NULL) {
        return -1;
    }

    No *atual = (*refFila)->inicio;

    int i = 0;
    while (atual != NULL) {
        if (i == posicao) return atual->valor;
        atual = atual->prox;
        i++;
    }

    return -1;
}


#ifndef LOGTREE_H
#define LOGTREE_H

typedef struct node {
    int conta; 
    int classe;
    int timer; 
    int caixa;
    int tempo;
    struct node *esq, *dir;
} Node;

typedef struct {
    Node *raiz;
} Log;

void LogInicializar(Log **I);
void LogRegistrar(Log **I, int conta, int classe, int timer, int caixa, int tempo);
float LogMediaPorClasse(Log **I, int classe);
int LogPegaSomaPorClasse(Log **I, int classe);    
int LogPegaContagemPorClasse(Log **I, int classe); 

#endif
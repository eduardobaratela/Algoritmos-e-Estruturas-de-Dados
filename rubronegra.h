#ifndef RUBRONEGRA
#define RUBRONEGRA
#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct item{
    int chave;
}t_item;

typedef struct node{
    t_item item;
    struct node* esq;
    struct node* dir;
    struct node* pai;
    int cor;
}t_node;

typedef t_node* t_arvore;

struct arvore{
    t_arvore raiz;
};

typedef struct arvore* t_apontador;

t_arvore Null = NULL;

t_apontador criaArvore();
t_arvore criaRaiz(int key);
int cor(t_arvore tree);
void rot_esq(t_apontador arvore, t_arvore tree);
void rot_dir(t_apontador arvore, t_arvore tree);
void balanceia(t_apontador arvore, t_arvore novo);
void insere(t_apontador tree, int key);
void libera(t_arvore atual);
void inOrdem(t_arvore tree);
void preOrdem(t_arvore tree);
void posOrdem(t_arvore tree);
void max(t_arvore tree);
void min(t_arvore tree);
t_arvore busca(t_arvore tree, int chave);
void sucessor(t_arvore tree, int key); 
void predecessor(t_arvore tree, int key);

#endif

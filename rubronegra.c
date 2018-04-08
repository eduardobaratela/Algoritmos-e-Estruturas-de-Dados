#include <stdio.h>
#include <stdlib.h>
#include "rubronegra.h"

t_apontador criaArvore(){
    if(Null == NULL) {
        Null = (t_node*) malloc(sizeof(t_node));
        Null->cor = BLACK;
        Null->dir = Null;
        Null->esq = Null;
        Null->pai = Null;
    }
    t_apontador novaArvore = (t_apontador) malloc(sizeof(struct arvore));
    novaArvore->raiz = Null;
   
    return novaArvore;
}

t_arvore criaRaiz(int key){
    t_arvore tree = (t_node*) malloc(sizeof(t_node));
    tree->dir = Null;
    tree->esq = Null;
    tree->pai = Null;
    tree->item.chave = key;
    tree->cor = RED;
    
    return tree;
}

int cor(t_arvore tree){
    if(tree == NULL) return BLACK;
    
    return tree->cor;
}

void rot_esq(t_apontador arvore, t_arvore tree){
    t_arvore aux;
    
    aux = tree->dir;
    tree->dir = aux->esq;
    if (aux->esq != Null) aux->esq->pai = tree;
    aux->pai = tree->pai;
    if(tree->pai == Null) arvore->raiz = aux;
    if(tree == tree->pai->esq) tree->pai->esq = aux;
    else if(tree == tree->pai->dir) tree->pai->dir = aux;
    aux->esq = tree;
    tree->pai = aux;
}

void rot_dir(t_apontador arvore, t_arvore tree){
     t_arvore aux;
    
    aux = tree->esq;
    tree->esq = aux->dir;
    if (aux->dir != Null) aux->dir->pai = tree;
    aux->pai = tree->pai;
    if(tree->pai == Null) arvore->raiz = aux;
    if(tree == tree->pai->dir) tree->pai->dir = aux;
    else if(tree == tree->pai->esq)tree->pai->esq = aux;
    aux->dir = tree;
    tree->pai = aux;
}

void balanceia(t_apontador arvore, t_arvore novo){
    t_arvore tio;
    while(cor(novo->pai) == RED) {            
        if(novo->pai == novo->pai->pai->esq) {
            tio = novo->pai->pai->dir;
            if(cor(tio) == RED) {           
                novo->pai->cor = BLACK;    
                tio->cor = BLACK;
                novo->pai->pai->cor = RED;
                novo = novo->pai->pai;
            } 
            else{
                if(novo == novo->pai->dir) {
                    novo = novo->pai;
                    rot_esq(arvore, novo);
                }
                novo->pai->cor = BLACK;
                novo->pai->pai->cor = RED;
                rot_dir(arvore, novo->pai->pai);
            }
        } 
        else{
            tio = novo->pai->pai->esq;
            if(cor(tio) == RED) {          
                novo->pai->cor = BLACK;
                tio->cor = BLACK;
                novo->pai->pai->cor = RED;
                novo = novo->pai->pai;
            } 
            else{
                if(novo == novo->pai->esq) {
                    novo = novo->pai;
                    rot_dir(arvore, novo);
                }
                novo->pai->cor = BLACK;
                novo->pai->pai->cor = RED;
                rot_esq(arvore, novo->pai->pai);
            }    
        }
    }
    arvore->raiz->cor = BLACK;
}

void insere(t_apontador tree, int key){
    t_arvore aux; 
    t_arvore dad;
    t_arvore novo;
    
    novo = criaRaiz(key);
    dad = Null;
    aux = tree->raiz;
    
    while(aux != Null){
        dad = aux;
        if(novo->item.chave == aux->item.chave){
            printf("erro\n");
            return;
        }
        if(novo->item.chave < aux->item.chave) aux = aux->esq;
        else aux = aux->dir;
    }
    
    novo->pai = dad;
    if(dad == Null) tree->raiz = novo;
    else if(novo->item.chave < dad->item.chave) dad->esq = novo;
    else dad->dir = novo;
    
    novo->esq = Null;
    novo->dir = Null;
    novo->cor = RED;

    balanceia(tree, novo);
}

void libera(t_arvore atual){
    if(atual == Null) return;
    
    libera(atual->esq);
    libera(atual->dir);
    
    free(atual);
}

void inOrdem(t_arvore tree){
    if(tree != Null){
        inOrdem(tree->esq);
        printf("%d ", tree->item.chave);
        inOrdem(tree->dir);
    }
}

void preOrdem(t_arvore tree){
    if(tree != Null){
        printf("%d ", tree->item.chave);
        preOrdem(tree->esq);
        preOrdem(tree->dir);
    }
}

void posOrdem(t_arvore tree){
    if(tree != Null){
        posOrdem(tree->esq);
        posOrdem(tree->dir);
        printf("%d ", tree->item.chave);
    }
}

void max(t_arvore tree){  
    t_arvore aux = tree;
    if(tree == Null){
        printf("erro\n");
        return;
    }
    while(aux->dir != Null) aux = aux->dir;
    
    printf("%d\n", aux->item.chave);
}

void min(t_arvore tree){  
    t_arvore aux = tree;
    
    if(tree == Null){
        printf("erro\n");
        return;
    }
    
    while(aux->esq != Null) aux = aux->esq;
    
    printf("%d\n", aux->item.chave);
}

t_arvore busca(t_arvore tree, int chave){
    if(tree == Null) return Null;
    if(tree->item.chave == chave) return tree;
    if(tree->item.chave > chave ) return busca(tree->esq, chave);
    else return busca(tree->dir, chave);
}

void sucessor(t_arvore tree, int key){    
    if(tree == Null){
        printf("erro\n");
        return;
    }    
    t_arvore aux = busca(tree, key);
    if(aux == Null){
        printf("erro\n");
        return;
    }
    
    if(aux->dir == Null){
        printf("erro\n");
        return;
    }
    aux = aux->dir;
    while(aux->esq != Null) aux = aux->esq; 
    
    printf("%d\n", aux->item.chave);
}

void predecessor(t_arvore tree, int key){
    if(tree == Null){
        printf("erro\n");
        return;
    }    
    t_arvore aux = busca(tree, key);
    if(aux == Null){
        printf("erro\n");
        return;
    }
    
    if(aux->esq  == Null){
        printf("erro\n");
        return;
    }    
    aux = aux->esq;
    while(aux->dir != Null) aux = aux->dir; 
    
    printf("%d\n", aux->item.chave);
}

#include "raylib.h"

#ifndef _TAD_H_
#define _TAD_H_

typedef struct nodoLGEnc {
  void *info;
  struct nodoLGEnc *prox;
} NodoLGEnc;

typedef NodoLGEnc NodoGCirc;
typedef NodoLGEnc NodoPGEnc;

typedef struct {
  NodoLGEnc *prim;
} ListaGEnc;

typedef ListaGEnc ListaGCirc;

typedef struct {
  NodoPGEnc *topo;
} PilhaGEnc;

// Funcao que cria uma lista generica
ListaGEnc *criaListaGEnc();

// Funcao que destroi uma lista generica
// void destroiListaGEnc(ListaGEnc *lista); // TODO: Codar isso

int insereInicioListaGEnc(ListaGEnc *lista, void *info);

// Percorre a lista
void percorreListaGEnc(ListaGEnc *lista, void (*cb)(void *));

// Lista Circular genérica

ListaGCirc *criaListaGCirc();

int insereInicioListaGCirc(ListaGCirc *lista, void *info);

// Percorre a lista circular
void percorreListaGCirc(ListaGCirc *lista, void (*cb)(void *, void *), void *teste);

// Pilha genérica

// Funcao que cria uma pilha
PilhaGEnc *criaPilhaEnc();

// Funcao que destroi uma pilha
void destroiPilhaEnc(PilhaGEnc *pilha);

// Funcao que insere um elemento na pilha
void empilhaPilhaEnc(PilhaGEnc *pilha, void *info);

// Funcao que remove um elemento da pilha
void *desempilhaPilhaEnc(PilhaGEnc *pilha);

// Funcao que determina se uma pilha eh vazia
bool vaziaPilhaEnc(PilhaGEnc *pilha);

#endif
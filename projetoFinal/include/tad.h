#include "raylib.h"

#ifndef _TAD_H_
#define _TAD_H_

typedef struct nodoLGEnc {
  void *info;
  struct nodoLGEnc *prox;
} NodoLGEnc;

typedef NodoLGEnc NodoGCirc;

typedef struct {
  NodoLGEnc *prim;
} ListaGEnc;

typedef ListaGEnc ListaGCirc;

// Funcao que cria uma lista generica
ListaGEnc *criaListaGEnc();

// Funcao que destroi uma lista generica
// void destroiListaGEnc(ListaGEnc *lista); // TODO: Codar isso

int insereInicioListaGEnc(ListaGEnc *lista, void *info);

// Percorre a lista
void percorreListaGEnc(ListaGEnc *lista, void (*cb)(void *));

ListaGCirc *criaListaGCirc();

int insereInicioListaGCirc(ListaGCirc *lista, void *info);

// Percorre a lista circular
void percorreListaGCirc(ListaGCirc *lista, void (*cb)(void *, void *), void *teste);

#endif
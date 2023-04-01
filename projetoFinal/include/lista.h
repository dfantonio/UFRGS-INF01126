#ifndef _LISTA_H_
#define _LISTA_H_

typedef struct nodoFGEnc {
  void *info;
  struct nodoFGEnc *prox;
} NodoLGEnc;

typedef struct {
  NodoLGEnc *prim;
} ListaGEnc;

// Funcao que cria uma lista generica
ListaGEnc *criaListaGEnc();

// Funcao que destroi uma lista generica
// void destroiListaGEnc(ListaGEnc *lista); // TODO: Codar isso

int insereInicioListaGEnc(ListaGEnc *lista, void *info);

// Percorre a lista
void percorreListaGEnc(ListaGEnc *lista, void (*cb)(void *));

#endif
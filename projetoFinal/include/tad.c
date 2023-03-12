#include "tad.h"
#include "jogo.h"
#include <stdlib.h>

ListaGEnc *criaListaGEnc() {
  ListaGEnc *lista = (ListaGEnc *)malloc(sizeof(ListaGEnc));
  if (lista)
    lista->prim = NULL;
  return lista;
}

int insereInicioListaGEnc(ListaGEnc *lista, void *info) {
  NodoLGEnc *novo = (NodoLGEnc *)malloc(sizeof(NodoLGEnc));
  if (novo == NULL) // Idealmente, sempre checar!
    return 0;
  novo->info = info;
  novo->prox = lista->prim;
  lista->prim = novo;
  return 1;
}

void percorreListaGEnc(ListaGEnc *lista, void (*cb)(void *)) {
  NodoLGEnc *aux;
  for (aux = lista->prim; aux != NULL; aux = aux->prox)
    cb(aux->info);
}

/**
 * Cria uma lista circular sem elementos
 */
ListaGCirc *criaListaGCirc() {
  ListaGCirc *lista = (ListaGCirc *)malloc(sizeof(ListaGCirc));
  if (lista)
    lista->prim = NULL;
  return lista;
}

/**
 * Insere no início de uma lista circular
 */
int insereInicioListaGCirc(ListaGCirc *lista, void *info) {
  NodoLGEnc *aux;
  NodoLGEnc *novo = (NodoLGEnc *)malloc(sizeof(NodoLGEnc));
  if (novo == NULL) // Idealmente, sempre checar!
    return 0;

  novo->info = info;

  if (lista->prim == NULL) {
    lista->prim = novo;
    novo->prox = lista->prim;
  } else {
    aux = lista->prim;
    while (aux->prox != lista->prim)
      aux = aux->prox;
    aux->prox = novo;
    novo->prox = lista->prim;
    lista->prim = novo;
  }
  return 1;
}

// TODO: Como passar o tipo jogo sem que tenha um importe cíclico entre tad.h e jogo.h?
// void percorreListaGCirc(ListaGCirc *lista, void (*cb)(void *, *Jogo), Jogo *jogo) {
void percorreListaGCirc(ListaGCirc *lista, void (*cb)(void *, void *), void *teste) {
  NodoGCirc *aux = lista->prim;

  cb(aux->info, teste);
  do {
    aux = aux->prox;
    cb(aux->info, teste);
  } while (aux->prox != lista->prim);
}

// Pilha genérica:

PilhaGEnc *criaPilhaGEnc() {
  PilhaGEnc *pilha = (PilhaGEnc *)malloc(sizeof(PilhaGEnc));
  if (pilha != NULL)
    pilha->topo = NULL;
  return pilha;
}

void destroiPilhaGEnc(PilhaGEnc *pilha) {
  NodoPGEnc *aux = pilha->topo;
  while (aux != NULL) {
    NodoPGEnc *tmp = aux->prox;
    free(aux);
    aux = tmp;
  }
  free(pilha);
}

void empilhaPilhaGEnc(PilhaGEnc *pilha, void *info) {
  NodoPGEnc *novo = (NodoPGEnc *)malloc(sizeof(NodoPGEnc));
  if (novo != NULL) { // Idealmente, sempre checar!
    novo->info = info;
    novo->prox = pilha->topo;
    pilha->topo = novo;
  }
}

void *desempilhaPilhaGEnc(PilhaGEnc *pilha) {
  NodoPGEnc *aux = pilha->topo;
  /* Aqui assumimos que desempilha eh
  chamada apenas se a pilha nao eh vazia */
  void *info = aux->info;
  pilha->topo = aux->prox;
  free(aux);
  return info;
}

bool vaziaPilhaGEnc(PilhaGEnc *pilha) {
  return (pilha->topo == NULL);
}

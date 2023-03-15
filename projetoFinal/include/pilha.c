#include "pilha.h"
#include <stdbool.h>
#include <stdlib.h>

// Pilha genérica:

PilhaGEnc *criaPilhaGEnc() {
  PilhaGEnc *pilha = (PilhaGEnc *)malloc(sizeof(PilhaGEnc));
  if (pilha != NULL) {
    pilha->topo = NULL;
    pilha->base = NULL;
  }
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
    if (pilha->base == NULL) pilha->base = novo;

    novo->info = info;
    novo->ant = NULL;
    novo->prox = pilha->topo;
    if (pilha->topo) pilha->topo->ant = novo;
    pilha->topo = novo;
  }
}

void *desempilhaPilhaGEnc(PilhaGEnc *pilha) {
  NodoPGEnc *aux = pilha->topo;
  /* Aqui assumimos que desempilha eh
  chamada apenas se a pilha nao eh vazia */
  void *info = aux->info;
  pilha->topo = aux->prox;
  if (!pilha->topo) pilha->base = NULL;
  if (pilha->topo) pilha->topo->ant = NULL;
  free(aux);
  return info;
}

bool vaziaPilhaGEnc(PilhaGEnc *pilha) {
  return (pilha->topo == NULL);
}

void percorrePilhaGEnc(PilhaGEnc *pilha, void (*cb)(void *, void *), void *jogo) {
  NodoPGEnc *aux = pilha->base;

  if (aux == NULL) return;
  do {
    cb(aux->info, jogo);
    aux = aux->ant;
  } while (aux != NULL);
}
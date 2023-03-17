#include "pilha.h"
#include <stdbool.h>
#include <stdlib.h>

// Pilha genérica:

PilhaGEnc *criaPilhaGEnc() {
  PilhaGEnc *pilha = (PilhaGEnc *)malloc(sizeof(PilhaGEnc));
  if (pilha != NULL) {
    pilha->topo = NULL;
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

void percorrePilhaGEnc(PilhaGEnc *pilha, void (*cb)(void *, void *), void *jogo) {
  NodoPGEnc *aux = pilha->topo;

  if (aux == NULL) return;
  do {
    cb(aux->info, jogo);
    aux = aux->prox;
  } while (aux != NULL);
}

void percorrePilhaReversoGEnc(PilhaGEnc *pilha, void (*cb)(void *, void *), void *jogo) {
  PilhaGEnc *temp = criaPilhaGEnc();
  NodoPGEnc *aux = pilha->topo;

  // Caso a pilha seja vazia não faz nada
  if (aux == NULL) return;

  // Inverte a pilha pra base ser o topo
  do {
    empilhaPilhaGEnc(temp, desempilhaPilhaGEnc(pilha));
    aux = pilha->topo;
  } while (aux != NULL);

  // Chama os callback na ordem invertida (correta)
  aux = temp->topo;
  do {
    cb(aux->info, jogo);
    aux = aux->prox;
  } while (aux != NULL);

  aux = temp->topo;
  do {
    empilhaPilhaGEnc(pilha, desempilhaPilhaGEnc(temp));
    aux = temp->topo;
  } while (aux != NULL);

  destroiPilhaGEnc(temp);
}
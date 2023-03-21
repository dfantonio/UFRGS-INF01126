#include <stdbool.h>

#ifndef _PILHA_H_
#define _PILHA_H_

typedef struct nodoPGEnc {
  void *info;
  struct nodoPGEnc *prox;
} NodoPGEnc;

typedef struct {
  NodoPGEnc *topo;
} PilhaGEnc;

// Pilha gen�rica

// Funcao que cria uma pilha
PilhaGEnc *criaPilhaGEnc();

// Funcao que destroi uma pilha
void destroiPilhaGEnc(PilhaGEnc *pilha);

// Funcao que insere um elemento na pilha
void empilhaPilhaGEnc(PilhaGEnc *pilha, void *info);

// Funcao que remove um elemento da pilha
void *desempilhaPilhaGEnc(PilhaGEnc *pilha);

// Funcao que determina se uma pilha eh vazia
bool vaziaPilhaGEnc(PilhaGEnc *pilha);

// Percorre a pilha a partir do topo para a base
void percorrePilhaGEnc(PilhaGEnc *pilha, void (*cb)(void *, void *), void *jogo);

// Percorre a pilha a partir da base para o topo
void percorrePilhaReversoGEnc(PilhaGEnc *pilha, void (*cb)(void *, void *), void *jogo);

#endif
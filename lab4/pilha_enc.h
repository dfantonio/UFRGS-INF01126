#ifndef _PILHA_ENC_H_
#define _PILHA_ENC_H_

#include "lista_enc.h"

typedef NodoLEnc NodoPEnc;

typedef struct pilhaEnc{
   NodoPEnc *topo;
} PilhaEnc;

// Funcao que cria uma pilha
PilhaEnc* criaPilhaEnc();

// Funcao que destroi uma pilha
void destroiPilhaEnc(PilhaEnc *pilha);

// Funcao que insere um elemento na pilha
void empilhaPilhaEnc(PilhaEnc *pilha, Info info);

// Funcao que remove um elemento da pilha
Info desempilhaPilhaEnc(PilhaEnc *pilha);

// Funcao que determina se uma pilha eh vazia
int vaziaPilhaEnc(PilhaEnc* pilha);

#endif

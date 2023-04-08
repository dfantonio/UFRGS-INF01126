#include "fila.h"
#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma fila
FilaGEnc *criaFilaGEnc() {
  FilaGEnc *fila = (FilaGEnc *)malloc(sizeof(FilaGEnc));
  if (fila != NULL) { // Idealmente, sempre checar!
    fila->ini = NULL;
    fila->fim = NULL;
  }
  return fila;
}

// Funcao que destroi uma fila
void destroiFilaGEnc(FilaGEnc *fila) {
  NodoFEnc *aux = fila->ini;
  while (aux != NULL) {
    NodoFEnc *tmp = aux->prox;
    free(aux); // Cuidar ordem do free
    aux = tmp;
  }
  free(fila);
}

// Funcao que insere um elemento na fila
void enfileiraFilaGEnc(FilaGEnc *fila, void *info) {
  NodoFEnc *novo = (NodoFEnc *)malloc(sizeof(NodoFEnc));
  if (fila != NULL) {
    novo->info = info;
    novo->prox = NULL;
    if (fila->fim != NULL)
      fila->fim->prox = novo;
    else
      fila->ini = novo;
    fila->fim = novo;
  }
}

// Funcao que remove um elemento da fila
void *desenfileiraFilaGEnc(FilaGEnc *fila) {
  NodoFEnc *aux = fila->ini;
  void *info = aux->info;
  fila->ini = aux->prox;
  if (fila->ini == NULL)
    fila->fim = NULL;
  free(aux);
  return info;
}

void percorreFilaGEnc(FilaGEnc *fila, void (*cb)(void *, void *), void *jogo) {
  Carta *info;
  FilaGEnc *filaAux = criaFilaGEnc();
  while (!vaziaFilaGEnc(fila)) {
    info = desenfileiraFilaGEnc(fila);
    cb(info, jogo);
    enfileiraFilaGEnc(filaAux, info);
  }
  while (!vaziaFilaGEnc(filaAux)) {
    info = desenfileiraFilaGEnc(filaAux);
    enfileiraFilaGEnc(fila, info);
  }
  destroiFilaGEnc(filaAux);
}

void *percorreFilaReversoGEnc(FilaGEnc *fila, bool (*cb)(void *, void *), void *jogo) {
  Carta *info, *cartaInfo = NULL, *aux;
  FilaGEnc *filaAux = criaFilaGEnc();
  PilhaGEnc *pilhaAux = criaPilhaGEnc();
  bool resultado = false, entrou = false;

  while (!vaziaFilaGEnc(fila)) {
    info = desenfileiraFilaGEnc(fila);
    empilhaPilhaGEnc(pilhaAux, info);
    enfileiraFilaGEnc(filaAux, info);
  }
  while (!vaziaFilaGEnc(filaAux)) {
    info = desenfileiraFilaGEnc(filaAux);
    aux = desempilhaPilhaGEnc(pilhaAux);
    if (!resultado) resultado = cb(aux, jogo);

    if (resultado && !entrou) {
      cartaInfo = aux;
      entrou = true;
    }

    enfileiraFilaGEnc(fila, info);
  }

  destroiFilaGEnc(filaAux);
  destroiPilhaGEnc(pilhaAux);

  return cartaInfo;
}

// Funcao que determina se uma fila eh vazia
int vaziaFilaGEnc(FilaGEnc *fila) {
  return (fila->ini == NULL);
}

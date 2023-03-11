#include "tad.h"
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
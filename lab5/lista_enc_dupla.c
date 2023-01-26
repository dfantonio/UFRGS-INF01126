#include "lista_enc_dupla.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma lista
ListaEnc2 *criaListaEnc2()
{
  ListaEnc2 *lista = (ListaEnc2 *)malloc(sizeof(ListaEnc2));
  if (lista != NULL)    // Idealmente, sempre checar!
    lista->prim = NULL; // Representacao de lista vazia
  return lista;
}

// Funcao que destroi uma lista
void destroiListaEnc2(ListaEnc2 *lista)
{
  NodoLEnc2 *aux = lista->prim;
  while (aux != NULL)
  {
    NodoLEnc2 *tmp = aux->prox;
    free(aux); // Cuidar ordem do free
    aux = tmp;
  }
  free(lista);
}

// Funcao que imprime todos os nodos de uma lista
void imprimeListaEnc2(ListaEnc2 *lista)
{
  NodoLEnc2 *aux;
  printf("-----------------------------------------\n");
  for (aux = lista->prim; aux != NULL; aux = aux->prox)
    printf("%d | %s (%s)\n", aux->info.chave,
           aux->info.nome,
           aux->info.email);
  printf("-----------------------------------------\n");
}

// Funcao que resgata um nodo com uma informacao de uma lista
NodoLEnc2 *buscaInfoListaEnc2(ListaEnc2 *lista, int chave)
{
  NodoLEnc2 *aux;
  for (aux = lista->prim; aux != NULL; aux = aux->prox)
    if (aux->info.chave == chave)
      return aux;
  return NULL;
}

// Funcao que insere um nodo no inicio de uma lista
int insereInicioListaEnc2(ListaEnc2 *lista, Info info)
{
  NodoLEnc2 *novo = (NodoLEnc2 *)malloc(sizeof(NodoLEnc2));
  if (novo == NULL) // Idealmente, sempre checar!
    return 0;
  novo->info = info;
  novo->ant = NULL;
  novo->prox = lista->prim;
  if (lista->prim != NULL)
    lista->prim->ant = novo;
  lista->prim = novo;
  return 1;
}

// Funcao que remove um nodo com uma informacao de uma lista
int removeInfoListaEnc2(ListaEnc2 *lista, int chave)
{
  NodoLEnc2 *aux = lista->prim;
  while (aux != NULL && aux->info.chave != chave)
  {
    aux = aux->prox;
  }
  if (aux != NULL)
  {
    if (aux->ant == NULL)
    {
      lista->prim = aux->prox;
      if (aux->prox != NULL)
        aux->prox->ant = NULL;
    }
    else
    {
      aux->ant->prox = aux->prox;
      if (aux->prox != NULL)
        aux->prox->ant = aux->ant;
    }
    free(aux);
    return 1;
  }
  return 0; // Nao encontrou
}

int inserePosListaEnc2(ListaEnc2 *lista, Info info, int pos)
{
  if (pos < 0)
    return 0;

  NodoLEnc2 *novo = (NodoLEnc2 *)malloc(sizeof(NodoLEnc2));
  NodoLEnc2 *infoAux = lista->prim;
  if (novo == NULL) // Idealmente, sempre checar!
    return 0;
  novo->info = info;

  // a lista ta vazia
  if (infoAux == NULL)
  {
    if (pos != 0)
      return 0;

    lista->prim = novo;
    novo->ant = NULL;
    novo->prox = NULL;
    return 1;
  }

  // Caso deseje gravar no primeiro elemento
  if (pos == 0)
  {
    novo->ant = NULL;
    novo->prox = lista->prim;
    lista->prim->ant = novo;
    lista->prim = novo;
  }
  else
  {
    pos--;
    for (; pos > 0; pos--)
    {
      infoAux = infoAux->prox;
      if (infoAux == NULL)
        return 0;
    }

    novo->prox = infoAux->prox;
    novo->ant = infoAux;
    infoAux->prox = novo;

    if (novo->prox)
      novo->prox->ant = novo;
  }

  return 1;
}

ListaEnc2 *copiaListaEnc2(ListaEnc2 *lista)
{
  ListaEnc2 *novaLista = criaListaEnc2();
  NodoLEnc2 *infoAux = lista->prim, *tempFuturo = lista->prim;

  for (int aux = 0; tempFuturo != NULL; tempFuturo = tempFuturo->prox)
    infoAux = tempFuturo;

  for (; infoAux != NULL; infoAux = infoAux->ant)
    insereInicioListaEnc2(novaLista, infoAux->info);

  return novaLista;
}

void inverteListaEnc2(ListaEnc2 *lista)
{
  NodoLEnc2 *infoAux = lista->prim;
  NodoLEnc2 *prox;

  for (; infoAux != NULL; infoAux = infoAux->ant)
  {
    prox = infoAux->prox;

    infoAux->prox = infoAux->ant;
    infoAux->ant = prox;

    lista->prim = infoAux;
  }
}

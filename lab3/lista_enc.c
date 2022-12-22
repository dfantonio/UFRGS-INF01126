#include "lista_enc.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma lista
ListaEnc *criaListaEnc()
{
  ListaEnc *lista = (ListaEnc *)malloc(sizeof(ListaEnc));
  if (lista != NULL)    // Idealmente, sempre checar!
    lista->prim = NULL; // Representacao de lista vazia
  return lista;
}

// Funcao que destroi uma lista
void destroiListaEnc(ListaEnc *lista)
{
  NodoLEnc *aux = lista->prim;
  while (aux != NULL)
  {
    NodoLEnc *tmp = aux->prox;
    free(aux); // Cuidar ordem do free
    aux = tmp;
  }
  free(lista);
}

// Funcao que imprime todos os nodos de uma lista
void imprimeListaEnc(ListaEnc *lista)
{
  NodoLEnc *aux;
  printf("-----------------------------------------\n");
  for (aux = lista->prim; aux != NULL; aux = aux->prox)
    printf("%d | %s (%s)\n", aux->info.chave,
           aux->info.nome,
           aux->info.email);
  printf("-----------------------------------------\n");
}

// Funcao que insere um nodo no inicio de uma lista
int insereInicioListaEnc(ListaEnc *lista, Info info)
{
  NodoLEnc *novo = (NodoLEnc *)malloc(sizeof(NodoLEnc));
  if (novo == NULL) // Idealmente, sempre checar!
    return 0;
  novo->info = info;
  novo->prox = lista->prim;
  lista->prim = novo;
  return 1;
}

// Funcao que insere um nodo no final de uma lista
int insereFimListaEnc(ListaEnc *lista, Info info)
{
  NodoLEnc *novo = (NodoLEnc *)malloc(sizeof(NodoLEnc));
  if (novo == NULL) // Idealmente, sempre checar!
    return 0;

  NodoLEnc *aux = lista->prim;
  if (lista->prim == NULL)
  {
    lista->prim = novo;
  }
  else
  {
    while (aux->prox != NULL)
      aux = aux->prox;
    aux->prox = novo;
  }

  novo->info = info;
  novo->prox = NULL;
  return 1;
}

// Funcao que resgata um nodo com uma informacao de uma lista
NodoLEnc *buscaInfoListaEnc(ListaEnc *lista, int chave)
{
  NodoLEnc *aux;
  for (aux = lista->prim; aux != NULL; aux = aux->prox)
    if (aux->info.chave == chave)
      return aux;
  return NULL;
}

// Funcao que remove um nodo com uma informacao de uma lista
int removeInfoListaEnc(ListaEnc *lista, int chave)
{
  NodoLEnc *ant = NULL;
  NodoLEnc *aux = lista->prim;
  while (aux != NULL && aux->info.chave != chave)
  {
    ant = aux;
    aux = aux->prox;
  }
  if (aux != NULL)
  {
    if (ant == NULL)
      lista->prim = aux->prox;
    else
      ant->prox = aux->prox;
    free(aux);
    return 1;
  }
  return 0; // Nao encontrou
}

int concatenaListaEnc(ListaEnc *listaA, ListaEnc *listaB)
{
  NodoLEnc *contador;
  Info info;
  int retorno;
  for (contador = listaB->prim; contador != NULL; contador = contador->prox)
    if (!insereFimListaEnc(listaA, contador->info))
      return 0;
  return 1;
}

int insereUnicoListaEnc(ListaEnc *lista, Info info)
{
  NodoLEnc *contador;
  for (contador = lista->prim; contador != NULL; contador = contador->prox)
    if (contador->info.chave == info.chave)
      return 0;

  return insereFimListaEnc(lista, info);
}

// Insere um novo dado na posicao correta assumindo uma lista ordenada
int insereOrdenadoLista(ListaEnc *lista, Info info)
{
  NodoLEnc *contador;
  NodoLEnc *novo = (NodoLEnc *)malloc(sizeof(NodoLEnc));
  if (novo == NULL)
    return 0;

  if (lista->prim == NULL)
  {
    return insereFimListaEnc(lista, info);
  }

  for (contador = lista->prim; contador->prox != NULL; contador = contador->prox)
  {
    if (contador->info.chave < info.chave && contador->prox->info.chave > info.chave)
    {
      novo->info = info;
      novo->prox = contador->prox;
      contador->prox = novo;
    }
  }

  return 1;
}

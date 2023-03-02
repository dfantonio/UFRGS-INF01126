#include "abp.h"
#include <stdlib.h>
#include <stdio.h>

// Funcao que cria uma ABP
ABP *criaABP()
{
  ABP *arv = (ABP *)malloc(sizeof(ABP));
  if (arv)
    arv->raiz = NULL;
  return arv;
}

// Funcao auxiliar para imprimir uma ABP
void imprimeNodoABP(NodoABin *raiz)
{
  if (raiz != NULL)
  {
    imprimeNodoABP(raiz->esq);
    printf("%d | %s (%s)\n", raiz->info.chave,
           raiz->info.nome,
           raiz->info.email);
    imprimeNodoABP(raiz->dir);
  }
}

// Funcao que imprime uma ABP
void imprimeABP(ABP *arv)
{
  printf("-----------------------------------------\n");
  imprimeNodoABP(arv->raiz);
  printf("-----------------------------------------\n");
}

// Funcao que auxiliar para inserir um elemento na ABP
NodoABin *insereNodoABP(NodoABin *raiz, Info info)
{
  if (raiz == NULL)
  {
    raiz = (NodoABin *)malloc(sizeof(NodoABin));
    if (raiz)
    {
      raiz->info = info;
      raiz->esq = NULL;
      raiz->dir = NULL;
    }
  }
  else if (info.chave < raiz->info.chave)
    raiz->esq = insereNodoABP(raiz->esq, info);
  else
    raiz->dir = insereNodoABP(raiz->dir, info);
  return raiz;
}

// Funcao que insere um elemento na ABP
void insereABP(ABP *arv, Info info)
{
  arv->raiz = insereNodoABP(arv->raiz, info);
}

// Funcao auxiliar para buscar uma informacao na ABP
Info buscaInfoNodoABP(NodoABin *raiz, int chave)
{
  if (raiz == NULL)
  {
    Info infoAux = {-1, "", ""}; // chave, nome, email
    return infoAux;
  }
  else if (raiz->info.chave > chave)
    return buscaInfoNodoABP(raiz->esq, chave);
  else if (raiz->info.chave < chave)
    return buscaInfoNodoABP(raiz->dir, chave);
  else
    return raiz->info;
}

// Funcao que busca uma informacao na ABP
Info buscaInfoABP(ABP *arv, int chave)
{
  return buscaInfoNodoABP(arv->raiz, chave);
}

// Funcao auxiliar para remover uma informacao da ABP
NodoABin *removeInfoNodoABP(NodoABin *raiz, int chave)
{
  if (raiz == NULL)
    return NULL;
  else if (raiz->info.chave > chave)
    raiz->esq = removeInfoNodoABP(raiz->esq, chave);
  else if (raiz->info.chave < chave)
    raiz->dir = removeInfoNodoABP(raiz->dir, chave);
  else
  {
    if (raiz->esq == NULL && raiz->dir == NULL)
    {
      free(raiz);
      raiz = NULL;
    }
    else if (raiz->esq == NULL)
    {
      NodoABin *tmp = raiz;
      raiz = raiz->dir;
      free(tmp);
    }
    else if (raiz->dir == NULL)
    {
      NodoABin *tmp = raiz;
      raiz = raiz->esq;
      free(tmp);
    }
    else
    {
      NodoABin *tmp = raiz->esq;
      while (tmp->dir != NULL)
        tmp = tmp->dir;
      raiz->info = tmp->info;
      tmp->info.chave = chave;
      raiz->esq = removeInfoNodoABP(raiz->esq, chave);
    }
  }
  return raiz;
}

// Funcao que remove uma informacao da ABP
void removeInfoABP(ABP *arv, int chave)
{
  arv->raiz = removeInfoNodoABP(arv->raiz, chave);
}

// Funcao auxiliar para destroir uma ABP
void destroiNodoABP(NodoABin *raiz)
{
  if (raiz != NULL)
  {
    destroiNodoABP(raiz->esq);
    destroiNodoABP(raiz->dir);
    free(raiz);
  }
}

// Funcao que destroi uma ABP
void destroiABP(ABP *arv)
{
  destroiNodoABP(arv->raiz);
  free(arv);
}

void imprimeNodoParentesesAninhados(NodoABin *raiz)
{
  if (raiz != NULL)
  {
    printf("%d(", raiz->info.chave);
    imprimeNodoParentesesAninhados(raiz->esq);
    printf(")(");
    imprimeNodoParentesesAninhados(raiz->dir);
    printf(")");
  }
}

void imprimeABPParentesesAninhados(ABP *arv)
{
  printf("-----------------------------------------\n");
  imprimeNodoParentesesAninhados(arv->raiz);
  printf("\n-----------------------------------------\n");
}

int minimoABP(ABP *arv)
{
  int resultado = -1;

  NodoABin *nodo = arv->raiz;
  while (nodo != NULL)
  {
    resultado = nodo->info.chave;
    nodo = nodo->esq;
  }

  return resultado;
}

void maximoNodoABP(NodoABin *raiz, int *valor)
{
  if (raiz != NULL)
  {
    if (raiz->info.chave > *valor)
      *valor = raiz->info.chave;
    maximoNodoABP(raiz->dir, valor);
  }
}

int maximoABP(ABP *arv)
{
  int maximo = -1;

  maximoNodoABP(arv->raiz, &maximo);

  return maximo;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo_ma.h"

// Funcao auxiliar que retorna o indice de um nodo em um grafo
int buscaNodoGrafoMA(GrafoMA *grafo, int chave);

// Funcao que cria um grafo
GrafoMA *criaGrafoMA(int maxVertices)
{
  int i, j;
  GrafoMA *grafo = (GrafoMA *)malloc(sizeof(GrafoMA));
  grafo->infos = (Info *)malloc(sizeof(Info) * maxVertices);
  grafo->adjacencias = (int **)malloc(sizeof(int *) * maxVertices);
  for (i = 0; i < maxVertices; i++)
  {
    grafo->adjacencias[i] = (int *)malloc(sizeof(int) * maxVertices);
    for (j = 0; j < maxVertices; j++)
      grafo->adjacencias[i][j] = 0;
  }
  grafo->maxVertices = maxVertices;
  grafo->numVertices = 0;
  return grafo;
}

// Funcao que insere um nodo em um grafo
int insereNodoGrafoMA(GrafoMA *grafo, Info info)
{
  if (grafo->numVertices < grafo->maxVertices && buscaNodoGrafoMA(grafo, info.chave) == -1)
  {
    grafo->infos[grafo->numVertices] = info;
    grafo->numVertices += 1;
    return 1;
  }
  return 0;
}

// Funcao que insere uma aresta em um grafo
int insereArestaGrafoMA(GrafoMA *grafo, int chave1, int chave2)
{
  // Verifica se os nodos são diferentes
  if (chave1 == chave2)
    return 0;
  int indice1 = buscaNodoGrafoMA(grafo, chave1);
  int indice2 = buscaNodoGrafoMA(grafo, chave2);

  // Verifica se os nodos existem
  if (indice1 == -1 || indice2 == -1)
    return 0;

  int jaExiste = grafo->adjacencias[indice1][indice2];

  if (jaExiste)
    return 0;

  grafo->adjacencias[indice1][indice2] = 1;
  grafo->adjacencias[indice2][indice1] = 1;
  return 1;
}

// Funcao que remove uma aresta de um grafo
int removeArestaGrafoMA(GrafoMA *grafo, int chave1, int chave2)
{
  int indice1 = buscaNodoGrafoMA(grafo, chave1);
  int indice2 = buscaNodoGrafoMA(grafo, chave2);

  // Verifica se os nodos existem
  if (indice1 == -1 || indice2 == -1)
    return 0;

  int jaExiste = grafo->adjacencias[indice1][indice2];

  if (!jaExiste)
    return 0;

  grafo->adjacencias[indice1][indice2] = 0;
  grafo->adjacencias[indice2][indice1] = 0;
  return 1;
}

// Funcao que imprime nodos e arestas de um grafo
void imprimeGrafoMA(GrafoMA *grafo)
{
  // Implementar
  printf("Vertices:\n");
  for (int i = 0; i < grafo->numVertices; i++)
    printf("%d | %s (%s)\n", grafo->infos[i].chave, grafo->infos[i].nome, grafo->infos[i].email);

  printf("Arestas:\n");
  for (int i = 0; i < grafo->numVertices; i++)
  {
    for (int j = 0; j < i; j++)
    {
      int indice1 = buscaNodoGrafoMA(grafo, i);
      int indice2 = buscaNodoGrafoMA(grafo, j);

      if (grafo->adjacencias[i][j])
        printf("{%d, %d} \n", grafo->infos[i].chave, grafo->infos[j].chave);
      // printf("{%s, %s} \n", grafo->infos[i].nome, grafo->infos[j].nome);
    }
  }
}

// Funcao que destroi um grafo
void destroiGrafoMA(GrafoMA *grafo)
{
  int i;
  for (i = 0; i < grafo->maxVertices; i++)
    free(grafo->adjacencias[i]);
  free(grafo->adjacencias);
  free(grafo->infos);
  free(grafo);
}

// Funcao auxiliar que retorna o indice de um nodo em um grafo
int buscaNodoGrafoMA(GrafoMA *grafo, int chave)
{
  int i;
  for (i = 0; i < grafo->numVertices; i++)
    if (grafo->infos[i].chave == chave)
      return i;
  return -1;
}

int tamanhoGrafoMA(GrafoMA *grafo)
{
  int count = 0;
  for (int i = 0; i < grafo->numVertices; i++)
    for (int j = 0; j < i; j++)
      if (grafo->adjacencias[i][j])
        count++;

  return count;
}

int ordemGrafoMA(GrafoMA *grafo)
{
  return grafo->numVertices;
}

int menorGrauGrafoMA(GrafoMA *grafo)
{
  int menor = INT_MAX;
  int aux = 0;
  for (int i = 0; i < grafo->numVertices; i++)
  {
    aux = 0;
    for (int j = 0; j < grafo->numVertices; j++)
    {
      if (grafo->adjacencias[i][j])
        aux++;
    }
    if (aux < menor)
      menor = aux;
  }

  return menor;
}

int maiorGrauGrafoMA(GrafoMA *grafo)
{
  int maior = 0;
  int aux = 0;
  for (int i = 0; i < grafo->numVertices; i++)
  {
    aux = 0;
    for (int j = 0; j < grafo->numVertices; j++)
    {
      if (grafo->adjacencias[i][j])
        aux++;
    }
    if (aux > maior)
      maior = aux;
  }

  return maior;
}
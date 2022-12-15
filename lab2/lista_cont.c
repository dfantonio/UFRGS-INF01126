#include "lista_cont.h"
#include <stdio.h>

// Funcao que cria uma lista
void criaListaCont(ListaCont *lista)
{
  lista->ini = 0;
  lista->fim = 0;
}

// Funcao que destroi uma lista
void destroiListaCont(ListaCont *lista)
{
  lista->ini = 0;
  lista->fim = 0;
}

// Funcao que retorna a cardinalidade de uma lista
int tamanhoListaCont(ListaCont lista)
{
  return lista.fim - lista.ini;
}

// Funcao que insere um nodo em uma posicao de uma lista
int inserePosListaCont(ListaCont *lista, Info nodo, int pos)
{
  int indice;
  int tamLista = tamanhoListaCont(*lista);

  if (TAM_MAX_LISTA == tamLista) // verifica se a lista esta cheia
    return 0;

  if (pos < lista->ini || pos > lista->fim) // verifica se a posicao eh valida
    return 0;

  for (indice = lista->fim - 1; indice >= pos; indice--)
    lista->nodos[indice + 1] = lista->nodos[indice];
  lista->fim += 1;
  lista->nodos[pos] = nodo;

  return 1;
}

// Funcao que remove um nodo em uma posicao de uma lista
int removePosListaCont(ListaCont *lista, int pos)
{
  int indice;

  if (pos < lista->ini || pos >= lista->fim) // verifica se a posicao eh valida
    return 0;

  // Sempre puxa tudo para o comeco
  for (indice = pos; indice < lista->fim; indice++)
    lista->nodos[indice] = lista->nodos[indice + 1];
  lista->fim -= 1;

  return 1;
}

// Funcao que resgata um nodo de uma posicao de uma lista
Info buscaPosListaCont(ListaCont lista, int pos)
{
  if (pos < lista.ini || pos >= lista.fim)
  { // verifica se a posicao eh valida
    Info auxiliar;
    auxiliar.chave = -1; // um nodo com chave = -1 eh um nodo invalido
    return auxiliar;
  }
  return lista.nodos[pos];
}

// Funcao que resgata um nodo com uma informacao de uma lista
Info buscaInfoListaCont(ListaCont lista, int chave)
{
  int indice;
  for (indice = lista.ini; indice < lista.fim; indice++)
    if (lista.nodos[indice].chave == chave)
      return lista.nodos[indice];
  Info auxiliar;
  auxiliar.chave = -1; // um nodo com chave = -1 eh um nodo invalido
  return auxiliar;
}

// Funcao que imprime todos os nodos de uma lista
void imprimeListaCont(ListaCont lista)
{
  int i;
  printf("-----------------------------------------\n");
  for (i = lista.ini; i < lista.fim; i++)
    printf("%d | %s (%s)\n", lista.nodos[i].chave,
           lista.nodos[i].nome,
           lista.nodos[i].email);
  printf("-----------------------------------------\n");
}

void inverteListaCont(ListaCont listaA, ListaCont *listaB)
{
  listaB->ini = listaA.ini;
  listaB->fim = listaA.fim;

  int lengthA = listaA.fim - listaA.ini;
  for (int i = lengthA; i >= 0; i--)
  {
    listaB->nodos[lengthA - i] = listaA.nodos[i - 1];
  }
}

Info removeInfoListaCont(ListaCont *lista, int chave)
{
  Info temp = {-1, "", ""};
  int index = -1;

  for (int i = lista->ini; i < lista->fim; i++)
  {
    if (lista->nodos[i].chave == chave)
      index = i;
  }

  if (index < 0)
    return temp;

  temp = lista->nodos[index];
  removePosListaCont(lista, index);
  return temp;
}

int concatenaListaCont(ListaCont listaA, ListaCont *listaB)
{
  int sizeA = listaA.fim - listaA.ini;
  int sizeB = listaB->fim - listaB->ini;
  if ((sizeA + sizeB) > TAM_MAX_LISTA)
    return 0;

  listaB->fim = sizeA + sizeB;
  // Reordena a listaB para as posicoes necessarias
  for (int i = 0; i < sizeB; i++)
  {
    listaB->nodos[i + sizeA] = listaB->nodos[i];
  }

  // Insere os elementos da listaA no comeco
  for (int i = 0; i < sizeA; i++)
  {
    listaB->nodos[i] = listaA.nodos[i];
  }

  return 1;
}
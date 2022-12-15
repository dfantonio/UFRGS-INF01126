#ifndef _LISTA_CONT_H_
#define _LISTA_CONT_H_

#define TAM_MAX_NOME 40
#define TAM_MAX_EMAIL 25

#define TAM_MAX_LISTA 5

typedef struct
{
  int chave;
  char nome[TAM_MAX_NOME];
  char email[TAM_MAX_EMAIL];
} Aluno;

typedef Aluno Info;

typedef struct
{
  int ini;
  int fim;
  Info nodos[TAM_MAX_LISTA];
} ListaCont;

// Funcao que cria uma lista
void criaListaCont(ListaCont *lista);

// Funcao que destroi uma lista
void destroiListaCont(ListaCont *lista);

// Funcao que insere um nodo em uma posicao de uma lista
int inserePosListaCont(ListaCont *lista, Info nodo, int pos);

// Funcao que remove um nodo em uma posicao de uma lista
int removePosListaCont(ListaCont *lista, int pos);

// Funcao que retorna a cardinalidade de uma lista
int tamanhoListaCont(ListaCont lista);

// Funcao que resgata um nodo de uma posicao de uma lista
Info buscaPosListaCont(ListaCont lista, int pos);

// Funcao que resgata um nodo com uma informacao de uma lista
Info buscaInfoListaCont(ListaCont lista, int chave);

// Funcao que imprime todos os nodos de uma lista
void imprimeListaCont(ListaCont lista);

// Função que inverte a ordem da listaA e joga na listaB
void inverteListaCont(ListaCont listaA, ListaCont *listaB);

// Função que remove um elemento da lista e retorna o elemento deletado
Info removeInfoListaCont(ListaCont *lista, int chave);

// Funcao que concatena duas listas
int concatenaListaCont(ListaCont listaA, ListaCont *listaB);

#endif

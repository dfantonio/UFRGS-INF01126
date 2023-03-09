#ifndef _AVL_H_
#define _AVL_H_

#define TAM_MAX_NOME 40
#define TAM_MAX_EMAIL 25

typedef struct
{
  int chave;
  char nome[TAM_MAX_NOME];
  char email[TAM_MAX_EMAIL];
} Aluno;

typedef Aluno Info;

typedef struct nodoAVL
{
  int alt;
  Info info;
  struct nodoAVL *esq;
  struct nodoAVL *dir;
} NodoAVL;

typedef struct
{
  NodoAVL *raiz;
} AVL;

// Funcao que cria uma AVL
AVL *criaAVL();

// Funcao que imprime uma AVL
void imprimeAVL(AVL *arv);

// Funcao que insere um elemento na AVL
void insereAVL(AVL *arv, Info info);

// Funcao que busca uma informacao na AVL
Info buscaInfoAVL(AVL *arv, int chave);

// Funcao que destroi uma AVL
void destroiAVL(AVL *arv);

// Funcao que conta o numero de nodos de uma arvore
int tamanhoAVL(AVL *arv);

// Funcao que remove um nodo da arvore
int removeInfoAVL(AVL *arv, int chave);

void imprimeAVLParentesesAninhados(AVL *arv);

int contaFolhasAVL(AVL *arv);

#endif

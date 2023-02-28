#ifndef __ARVORE_BINARIA_H_
#define __ARVORE_BINARIA_H_

#define TAM_MAX_NOME 40
#define TAM_MAX_EMAIL 25

typedef struct
{
  int chave;
  char nome[TAM_MAX_NOME];
  char email[TAM_MAX_EMAIL];
} Aluno;

typedef Aluno Info;

typedef struct nodoABin
{
  Info info;
  struct nodoABin *esq;
  struct nodoABin *dir;
} NodoABin;

typedef struct
{
  NodoABin *raiz;
} ArvBinaria;

// Funcao que cria uma arvore
ArvBinaria *criaArvBinaria();

// Funcao que imprime uma arvore
void imprimeArvBinaria(ArvBinaria *arv);

// Funcao que insere um elemento na arvore
void insereArvBinaria(ArvBinaria *arv, Info info);

// Funcao que busca uma informacao na arvore
Info buscaInfoArvBinaria(ArvBinaria *arv, int chave);

// Funcao que remove uma informacao da arvore
void removeInfoArvBinaria(ArvBinaria *arv, int chave);

// Funcao que destroi uma arvore
void destroiArvBinaria(ArvBinaria *arv);

// Funcao que imprime uma arvore
void imprimeIndentadoArvBinaria(ArvBinaria *arv);

// Funcao que retorna 1 se a arvore eh degenerada e 0 caso contrario
int ehDegeneradaArvBinaria(ArvBinaria *arv);
#endif

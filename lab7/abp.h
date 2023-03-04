#ifndef _ABP_H_
#define _ABP_H_

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
} ABP;

// Funcao que cria uma ABP
ABP *criaABP();

// Funcao que imprime uma ABP
void imprimeABP(ABP *arv);

// Funcao que insere um elemento na ABP
void insereABP(ABP *arv, Info info);

// Funcao que busca uma informacao na ABP
Info buscaInfoABP(ABP *arv, int chave);

// Funcao que remove uma informacao da ABP
void removeInfoABP(ABP *arv, int chave);

// Funcao que destroi uma ABP
void destroiABP(ABP *arv);

// Funcao que imprime a arvore aninhada
void imprimeABPParentesesAninhados(ABP *arv);

// Funcao que encontra o menor valor da arvore
int minimoABP(ABP *arv);

int maximoABP(ABP *arv);

void imprimeReverso(ABP *arv);

#endif

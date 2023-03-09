#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

// Prototipos
int alturaNodoAVL(NodoAVL *raiz);
int fatorBalanceamentoNodoAVL(NodoAVL *raiz);
NodoAVL *rotacaoEsquerdaAVL(NodoAVL *raiz);
NodoAVL *rotacaoDireitaAVL(NodoAVL *raiz);
NodoAVL *rotacaoDireitaEsquerdaAVL(NodoAVL *raiz);
NodoAVL *rotacaoEsquerdaDireitaAVL(NodoAVL *raiz);

// Funcao que cria uma AVL
AVL *criaAVL()
{
  AVL *arv = (AVL *)malloc(sizeof(AVL));
  if (arv)
    arv->raiz = NULL;
  return arv;
}

// Funcao auxiliar para imprimir uma AVL
void imprimeNodoAVL(NodoAVL *raiz)
{
  if (raiz != NULL)
  {
    imprimeNodoAVL(raiz->esq);
    printf("%d | %s (%s)\n", raiz->info.chave,
           raiz->info.nome,
           raiz->info.email);
    imprimeNodoAVL(raiz->dir);
  }
}

// Funcao que imprime uma AVL
void imprimeAVL(AVL *arv)
{
  printf("-----------------------------------------\n");
  imprimeNodoAVL(arv->raiz);
  printf("-----------------------------------------\n");
}

// Funcao que retorna a altura de um nodo
int alturaNodoAVL(NodoAVL *raiz)
{
  if (raiz->esq != NULL && raiz->dir != NULL)
  {
    if (raiz->esq->alt < raiz->dir->alt)
      return raiz->dir->alt + 1;
    else
      return raiz->esq->alt + 1;
  }
  else if (raiz->esq != NULL)
    return raiz->esq->alt + 1;
  else if (raiz->dir != NULL)
    return raiz->dir->alt + 1;
  else
    return 1;
}

// Funcao que retorna o fator de balanceamento de um nodo
int fatorBalanceamentoNodoAVL(NodoAVL *raiz)
{
  if (raiz == NULL)
    return 0;
  if (raiz->esq != NULL && raiz->dir != NULL)
    return raiz->esq->alt - raiz->dir->alt;
  else if (raiz->esq != NULL)
    return raiz->esq->alt;
  else if (raiz->dir != NULL)
    return -raiz->dir->alt;
  return 0;
}

// Funcao que insere um elemento na AVL
NodoAVL *insereNodoAVL(NodoAVL *raiz, Info info)
{
  if (raiz == NULL)
  {
    raiz = (NodoAVL *)malloc(sizeof(NodoAVL));
    if (raiz)
    {
      raiz->info = info;
      raiz->alt = 1;
      raiz->esq = NULL;
      raiz->dir = NULL;
    }
    return raiz;
  }
  else if (info.chave < raiz->info.chave)
    raiz->esq = insereNodoAVL(raiz->esq, info);
  else if (info.chave > raiz->info.chave)
    raiz->dir = insereNodoAVL(raiz->dir, info);

  raiz->alt = alturaNodoAVL(raiz);
  int FB = fatorBalanceamentoNodoAVL(raiz);
  int FBEsq = fatorBalanceamentoNodoAVL(raiz->esq);
  int FBDir = fatorBalanceamentoNodoAVL(raiz->dir);

  if (FB == 2 && FBEsq == 1)
  {
    raiz = rotacaoDireitaAVL(raiz);
  }

  else if (FB == -2 && FBDir == -1)
  {
    raiz = rotacaoEsquerdaAVL(raiz);
  }

  else if (FB == -2 && FBDir == 1)
  {
    raiz = rotacaoDireitaEsquerdaAVL(raiz);
  }

  else if (FB == 2 && FBEsq == -1)
  {
    raiz = rotacaoEsquerdaDireitaAVL(raiz);
  }

  return raiz;
}

// Funcao que insere um elemento na AVL
void insereAVL(AVL *arv, Info info)
{
  arv->raiz = insereNodoAVL(arv->raiz, info);
}

// Funcao auxiliar para buscar uma informacao na AVL
Info buscaInfoNodoAVL(NodoAVL *raiz, int chave)
{
  if (raiz == NULL)
  {
    Info infoAux = {-1, "", ""}; // chave, nome, email
    return infoAux;
  }
  else if (raiz->info.chave > chave)
    return buscaInfoNodoAVL(raiz->esq, chave);
  else if (raiz->info.chave < chave)
    return buscaInfoNodoAVL(raiz->dir, chave);
  else
    return raiz->info;
}

// Funcao que busca uma informacao na AVL
Info buscaInfoAVL(AVL *arv, int chave)
{
  return buscaInfoNodoAVL(arv->raiz, chave);
}

// Funcao auxiliar para destroir uma AVL
void destroiNodoAVL(NodoAVL *raiz)
{
  if (raiz != NULL)
  {
    destroiNodoAVL(raiz->esq);
    destroiNodoAVL(raiz->dir);
    free(raiz);
  }
}

// Funcao que destroi uma AVL
void destroiAVL(AVL *arv)
{
  destroiNodoAVL(arv->raiz);
  free(arv);
}

// Rotacoes
// Rotacao simples a esquerda
NodoAVL *rotacaoEsquerdaAVL(NodoAVL *raiz)
{
  NodoAVL *tmp1;
  NodoAVL *tmp2;

  tmp1 = raiz;
  tmp2 = tmp1->dir;

  tmp1->dir = tmp2->esq;
  tmp2->esq = tmp1;

  tmp1->alt = alturaNodoAVL(tmp1);
  tmp2->alt = alturaNodoAVL(tmp2);

  return tmp2;
}

// Rotacao simples a direita
NodoAVL *rotacaoDireitaAVL(NodoAVL *raiz)
{
  NodoAVL *tmp1;
  NodoAVL *tmp2;

  tmp1 = raiz;
  tmp2 = tmp1->esq;

  tmp1->esq = tmp2->dir;
  tmp2->dir = tmp1;

  tmp1->alt = alturaNodoAVL(tmp1);
  tmp2->alt = alturaNodoAVL(tmp2);

  return tmp2;
}

// Rotacao esquerda-direita
NodoAVL *rotacaoEsquerdaDireitaAVL(NodoAVL *raiz)
{
  NodoAVL *tmp1;
  NodoAVL *tmp2;
  NodoAVL *tmp3;

  tmp1 = raiz;
  tmp2 = tmp1->esq;
  tmp3 = tmp1->esq->dir;

  tmp1->esq = tmp3->dir;
  tmp2->dir = tmp3->esq;
  tmp3->dir = tmp1;
  tmp3->esq = tmp2;

  tmp1->alt = alturaNodoAVL(tmp1);
  tmp2->alt = alturaNodoAVL(tmp2);
  tmp3->alt = alturaNodoAVL(tmp3);

  return tmp3;
}

// Rotacao direita-esquerda
NodoAVL *rotacaoDireitaEsquerdaAVL(NodoAVL *raiz)
{
  NodoAVL *tmp1;
  NodoAVL *tmp2;
  NodoAVL *tmp3;

  tmp1 = raiz;
  tmp2 = tmp1->dir;
  tmp3 = tmp1->dir->esq;

  tmp1->dir = tmp3->esq;
  tmp2->esq = tmp3->dir;
  tmp3->esq = tmp1;
  tmp3->dir = tmp2;

  tmp1->alt = alturaNodoAVL(tmp1);
  tmp2->alt = alturaNodoAVL(tmp2);
  tmp3->alt = alturaNodoAVL(tmp3);

  return tmp3;
}

void tamanhoNodoAVL(NodoAVL *nodo, int *contagem)
{
  if (nodo == NULL)
    return;

  *contagem += 1;
  tamanhoNodoAVL(nodo->esq, contagem);
  tamanhoNodoAVL(nodo->dir, contagem);
}

int tamanhoAVL(AVL *arv)
{
  int contagem = 0;
  if (arv->raiz == NULL)
    return 0;

  tamanhoNodoAVL(arv->raiz, &contagem);
  return contagem;
}

// Funcao auxiliar para remover uma informacao da AVL
NodoAVL *removeInfoNodoAVL(NodoAVL *raiz, int chave)
{
  if (raiz == NULL)
    return NULL;
  else if (raiz->info.chave > chave)
    raiz->esq = removeInfoNodoAVL(raiz->esq, chave);
  else if (raiz->info.chave < chave)
    raiz->dir = removeInfoNodoAVL(raiz->dir, chave);
  else
  {
    if (raiz->esq == NULL && raiz->dir == NULL)
    {
      free(raiz);
      raiz = NULL;
    }
    else if (raiz->esq == NULL)
    {
      NodoAVL *tmp = raiz;
      raiz = raiz->dir;
      free(tmp);
    }
    else if (raiz->dir == NULL)
    {
      NodoAVL *tmp = raiz;
      raiz = raiz->esq;
      free(tmp);
    }
    else
    {
      NodoAVL *tmp = raiz->esq;
      while (tmp->dir != NULL)
        tmp = tmp->dir;
      raiz->info = tmp->info;
      tmp->info.chave = chave;
      raiz->esq = removeInfoNodoAVL(raiz->esq, chave);
    }
  }

  // Devo rebalancear a arvore aqui

  if (raiz == NULL)
    return raiz;

  raiz->alt = alturaNodoAVL(raiz);
  int FB = fatorBalanceamentoNodoAVL(raiz);
  int FBEsq = fatorBalanceamentoNodoAVL(raiz->esq);
  int FBDir = fatorBalanceamentoNodoAVL(raiz->dir);

  if (FB == 2 && FBEsq == 1)
    raiz = rotacaoDireitaAVL(raiz);
  else if (FB == -2 && FBDir == -1)
    raiz = rotacaoEsquerdaAVL(raiz);
  else if (FB == -2 && FBDir == 1)
    raiz = rotacaoDireitaEsquerdaAVL(raiz);
  else if (FB == 2 && FBEsq == -1)
    raiz = rotacaoEsquerdaDireitaAVL(raiz);
  else if (FB == 2 && FBEsq == 0)
    raiz = rotacaoDireitaAVL(raiz);
  else if (FB == -2 && FBDir == 0)
    raiz = rotacaoEsquerdaAVL(raiz);

  return raiz;
}

// Funcao que remove uma informacao da AVL
int removeInfoAVL(AVL *arv, int chave)
{
  arv->raiz = removeInfoNodoAVL(arv->raiz, chave);

  // TODO: Arrumar isso aqui
  return 1;
}

void imprimeNodoParentesesAninhados(NodoAVL *raiz)
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

void imprimeAVLParentesesAninhados(AVL *arv)
{
  printf("-----------------------------------------\n");
  imprimeNodoParentesesAninhados(arv->raiz);
  printf("\n-----------------------------------------\n");
}

void contaFolhasNodo(NodoAVL *nodo, int *contagem)
{
  if (nodo == NULL)
    return;

  if (nodo->esq == NULL && nodo->dir == NULL)
    *contagem += 1;

  contaFolhasNodo(nodo->esq, contagem);
  contaFolhasNodo(nodo->dir, contagem);
}

int contaFolhasAVL(AVL *arv)
{
  int contagem = 0;
  contaFolhasNodo(arv->raiz, &contagem);

  return contagem;
}

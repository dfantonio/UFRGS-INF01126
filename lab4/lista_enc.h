#ifndef _LISTA_ENC_H_
#define _LISTA_ENC_H_

#define TAM_MAX_NOME 40
#define TAM_MAX_EMAIL 25

typedef struct{
   int matricula;
   char nome[TAM_MAX_NOME];
   char email[TAM_MAX_EMAIL];
} Aluno;

typedef Aluno Info;

typedef struct nodoLEnc{
   Info info;
   struct nodoLEnc *prox;
} NodoLEnc;

#endif

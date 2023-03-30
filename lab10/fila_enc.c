#include "fila_enc.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma fila
FilaEnc* criaFila(){
   FilaEnc *fila = (FilaEnc*)malloc(sizeof(FilaEnc));
   fila->ini = NULL;
   fila->fim = NULL;
   return fila;
}

// Funcao que destroi uma fila
void destroiFila(FilaEnc *fila){
   ListaNodo *aux = fila->ini;
   while(aux != NULL){
       ListaNodo *tmp = aux->prox;
       free(aux); // Cuidar ordem do free
       aux = tmp;
   }
   free(fila);
}

// Funcao que insere um elemento na fila
void enfileiraFila(FilaEnc *fila, int info){
   ListaNodo *novo = (ListaNodo*)malloc(sizeof(ListaNodo));
   novo->info = info;
   novo->prox = NULL;
   if (fila->fim != NULL)
      fila->fim->prox = novo;
   else
      fila->ini = novo;
   fila->fim = novo;
}

// Funcao que remove um elemento da fila
int desenfileiraFila(FilaEnc *fila){
   ListaNodo *aux = fila->ini; 
   int info = aux->info;
   fila->ini = aux->prox;
   if (fila->ini == NULL)
      fila->fim = NULL;
   free(aux);
   return info;
}

// Funcao que determina se uma fila eh vazia
int vaziaFila(FilaEnc *fila){
   return (fila->ini == NULL);
}


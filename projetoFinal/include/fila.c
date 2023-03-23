#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma fila
FilaGEnc* criaFilaGEnc(){
   FilaGEnc *fila = (FilaGEnc*)malloc(sizeof(FilaGEnc));
   if (fila != NULL){ // Idealmente, sempre checar!
      fila->ini = NULL;
      fila->fim = NULL;
   }
   return fila;
}

// Funcao que destroi uma fila
void destroiFilaGEnc(FilaGEnc *fila){
   NodoFEnc *aux = fila->ini;
   while(aux != NULL){
       NodoFEnc *tmp = aux->prox;
       free(aux); // Cuidar ordem do free
       aux = tmp;
   }
   free(fila);
}

// Funcao que insere um elemento na fila
void enfileiraFilaGEnc(FilaGEnc *fila, void* info){
   NodoFEnc *novo = (NodoFEnc*)malloc(sizeof(NodoFEnc));
   if (fila != NULL){
      novo->info = info;
      novo->prox = NULL;
      if (fila->fim != NULL)
         fila->fim->prox = novo;
      else
         fila->ini = novo;
      fila->fim = novo;
   }
}


// Funcao que remove um elemento da fila
void *desenfileiraFilaGEnc(FilaGEnc *fila){
   NodoFEnc *aux = fila->ini; 
   void* info = aux->info;
   fila->ini = aux->prox;
   if (fila->ini == NULL)
      fila->fim = NULL;
   free(aux);
   return info;
}

// Funcao que determina se uma fila eh vazia
int vaziaFilaGEnc(FilaGEnc *fila){
   return (fila->ini == NULL);
}


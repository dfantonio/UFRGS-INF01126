#ifndef _FILA_ENC_H_
#define _FILA_ENC_H_

#include "lista_enc.h"

typedef NodoLEnc NodoFEnc;

typedef struct FilaEnc{
   NodoFEnc *ini;
   NodoFEnc *fim;
} FilaEnc;

// Funcao que cria uma fila
FilaEnc* criaFilaEnc();

// Funcao que destroi uma fila
void destroiFilaEnc(FilaEnc *fila);

// Funcao que insere um elemento na fila
void enfileiraFilaEnc(FilaEnc *fila, Info info);

// Funcao que remove um elemento da fila
Info desenfileiraFilaEnc(FilaEnc *fila);

// Funcao que determina se uma fila eh vazia
int vaziaFilaEnc(FilaEnc* fila);


#endif

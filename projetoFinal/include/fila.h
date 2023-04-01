#ifndef _FILA_H_
#define _FILA_H_

typedef struct nodoFEnc {
  void *info;
  struct nodoFEnc *prox;
} NodoFEnc;

typedef struct FilaGEnc{
   NodoFEnc *ini;
   NodoFEnc *fim;
} FilaGEnc;

// Funcao que cria uma fila
FilaGEnc* criaFilaGEnc();

// Funcao que destroi uma fila
void destroiFilaGEnc(FilaGEnc *fila);

// Funcao que insere um elemento na fila
void enfileiraFilaGEnc(FilaGEnc *fila, void *info);

// Funcao que remove um elemento da fila
void *desenfileiraFilaGEnc(FilaGEnc *fila);

void percorreFilaGEnc(FilaGEnc *fila, void (*cb)(void *, void *), void *jogo);

// Funcao que determina se uma fila eh vazia
int vaziaFilaGEnc(FilaGEnc* fila);


#endif

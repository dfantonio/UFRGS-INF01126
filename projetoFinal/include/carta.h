#include "raylib.h"
#include "tad.h"

#ifndef _CARTA_H_
#define _CARTA_H_

#define CARTA_LARGURA 150
#define CARTA_ALTURA  200

typedef enum {
  ESPADAS,
  PAUS,
  OUROS,
  COPAS,
} Naipe;

typedef struct {
  int numero;
  Naipe naipe;
  Vector2 coordsSprite;
  Vector2 coordsMesa;
} Carta;

// Cria um baralho com as 52 cartas
ListaGEnc *criaBaralho();

// Percorre o baralho
void percorreBaralho(ListaGEnc *lista);

#endif
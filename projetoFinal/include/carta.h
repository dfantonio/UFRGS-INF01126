#include "lista.h"
#include "raylib.h"
#include "fila.h"

#ifndef _CARTA_H_
#define _CARTA_H_

#define CARTA_LARGURA 150
#define CARTA_ALTURA  200

#define TAMANHO_BARALHO 52

typedef enum {
  ESPADAS,
  PAUS,
  OUROS,
  COPAS,
} Naipe;

typedef enum {
  FUNDACAO,
  TABLEAU,
  ESTOQUE
} EstadosCarta;

typedef struct {
  int numero;
  Naipe naipe;
  Rectangle coordsSprite;
  Rectangle coordsMesa;
  bool viradaParaBaixo;
  EstadosCarta posicao;
  Vector2 posicaoAnterior;
} Carta;

typedef FilaGEnc FilaCartas;

// Cria um baralho com as 52 cartas
ListaGEnc *criaBaralho();

// Percorre o baralho
void percorreBaralho(ListaGEnc *lista);

// Renderiza uma carta
void renderizaCarta(void *info, void *jogoVar);

#endif
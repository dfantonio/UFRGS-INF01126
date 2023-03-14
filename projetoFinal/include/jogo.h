#include "carta.h"
#include "fila.h"
#include "pilha.h"
#include "raylib.h"

#ifndef _JOGO_H_
#define _JOGO_H_

#define FUNDACAO_OFFSET_X 450
#define FUNDACAO_OFFSET_Y 10

typedef struct {
  Texture2D texturaCartas;
  Texture2D texturaCartaVerso;
  Texture2D texturaSlot;
} Texturas;

typedef struct {
  PilhaGEnc *estoque;
  PilhaGEnc *descarte;
  Carta *estoqueTopo;
  Carta *descarteTopo;

  Vector2 mouseOffset;

  // pilha fundacao
  PilhaGEnc *fundacao[4];
  // pilha e lista pro tableau
  Texturas texturas;

  Carta *cartaEmMovimento;
} Jogo;

void criaCartas(Jogo *jogo);

Vector2 Rectangle2Vector(Rectangle rec);

#endif
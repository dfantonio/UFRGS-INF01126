#include "carta.h"
#include "raylib.h"
#include "tad.h"

#ifndef _JOGO_H_
#define _JOGO_H_

typedef struct {
  Texture2D texturaCartas;
  Texture2D texturaCartaVerso;
} Texturas;

typedef struct {
  ListaGCirc *estoque;
  Carta *estoqueTopo;
  Carta *descarteTopo;

  Vector2 mouseOffset;

  // pilha fundacao
  // pilha e lista pro tableau
  Texturas texturas;
} Jogo;

void criaCartas(Jogo *jogo);

Vector2 Rectangle2Vector(Rectangle rec);

#endif
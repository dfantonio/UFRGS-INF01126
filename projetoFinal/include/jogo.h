#include "carta.h"
#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include "raylib.h"

#ifndef _JOGO_H_
#define _JOGO_H_

#define FUNDACAO_OFFSET_X 450
#define FUNDACAO_OFFSET_Y 10

#define ESTOQUE_OFFSET_X 0
#define ESTOQUE_OFFSET_Y 10

#define TABLEAU_OFFSET_X 230
#define TABLEAU_OFFSET_Y 215
#define TABLEAU_OFFSET_DELTA_Y 36

#define ESTOQUE_OFFSET \
  CLITERAL(Rectangle) { ESTOQUE_OFFSET_X, ESTOQUE_OFFSET_Y, CARTA_LARGURA, CARTA_ALTURA }

#define TABLEAU_OFFSET \
  CLITERAL(Rectangle) { TABLEAU_OFFSET_X, TABLEAU_OFFSET_Y, CARTA_LARGURA, CARTA_ALTURA }

#define NUM_COLUNAS_TABLEAU 7
#define NUM_COLUNAS_FUNDACAO 4

typedef struct {
  Texture2D texturaCartas;
  Texture2D texturaCartaVerso;
  Texture2D texturaSlot;
  Texture2D texturaEstoque;
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
  PilhaGEnc *pilhaTableau[NUM_COLUNAS_TABLEAU];
  FilaGEnc *filaTableau[NUM_COLUNAS_TABLEAU];

  Texturas texturas;

  Carta *cartaEmMovimento;
  PilhaCartas *cartasEmMovimento;
} Jogo;

void criaLayoutJogo(Jogo *jogo);
Vector2 Rectangle2Vector(Rectangle rec);

bool isOrigemCartaEstoque(EstadosCarta posicaoCarta);
bool isOrigemCartaTableau(EstadosCarta posicaoCarta);
bool isOrigemCartaFundacao(EstadosCarta posicaoCarta);

#endif

#include "carta.h"
#include "jogo.h"
#include "tableau.h"
#include "raylib.h"
#include <stdlib.h>

void renderizaCartasTableau(void *info, void *jogoVar) {
  Carta *carta = (Carta *)info;
  Jogo *jogo = (Jogo *)jogoVar;
  
  percorrePilhaGEnc(jogo->tableau, renderizaCarta, jogo);
  Texture2D textura;
  if (carta->viradaParaBaixo) {
    textura = jogo->texturas.texturaCartaVerso;
    DrawTexture(textura, carta->coordsMesa.x, carta->coordsMesa.y, WHITE);
  } else {
    textura = jogo->texturas.texturaCartas;
    DrawTextureRec(textura, carta->coordsSprite, Rectangle2Vector(carta->coordsMesa), WHITE);
  }
}

void renderizaTableau(Jogo *jogo) {
  for (int i = 0; i < 7; i++) {
    DrawTexture(jogo->texturas.texturaCartaVerso, TABLEAU_OFFSET_X + (CARTA_LARGURA * i), TABLEAU_OFFSET_Y, WHITE);
  }
  percorrePilhaGEnc(jogo->tableau, renderizaCartasTableau, jogo);
  Vector2 mousePos = GetMousePosition();

  // Verifica um clique no estoque quando n�o tem nenhuma carta pra virar
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, ESTOQUE_OFFSET)) {
    if (vaziaPilhaGEnc(jogo->tableau)) {
      while (!vaziaPilhaGEnc(jogo->descarte)) {
        Carta *movimento = desempilhaPilhaGEnc(jogo->descarte);
        movimento->viradaParaBaixo = true;
        movimento->coordsMesa.x = 0;
        empilhaPilhaGEnc(jogo->estoque, movimento);
      }
      jogo->descarteTopo = NULL;
    }
  }
}
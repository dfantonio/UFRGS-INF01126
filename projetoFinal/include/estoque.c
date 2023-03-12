
#include "carta.h"
#include "jogo.h"
#include "raylib.h"

void renderizaCartas(void *info, void *texturas) {
  Carta *carta = (Carta *)info;

  Texture2D textura;
  if (carta->viradaParaBaixo) {
    textura = ((Texturas *)texturas)->texturaCartaVerso;
    DrawTexture(textura, carta->coordsMesa.x, carta->coordsMesa.y, WHITE);
  } else {
    textura = ((Texturas *)texturas)->texturaCartas;
    DrawTextureRec(textura, carta->coordsSprite, carta->coordsMesa, WHITE);
  }
}

void renderizaEstoque(Jogo *jogo) {
  percorreListaGCirc(jogo->estoque, renderizaCartas, &jogo->texturas);
}

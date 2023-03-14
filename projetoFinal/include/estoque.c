
#include "carta.h"
#include "jogo.h"
#include "raylib.h"
#include <stdlib.h>

void renderizaCartasEstoque(void *info, void *jogoVar) {
  Carta *carta = (Carta *)info;
  Jogo *jogo = (Jogo *)jogoVar;

  Texture2D textura;
  if (carta->viradaParaBaixo) {
    textura = jogo->texturas.texturaCartaVerso;
    DrawTexture(textura, carta->coordsMesa.x, carta->coordsMesa.y, WHITE);
    jogo->estoqueTopo = carta;
  } else {
    textura = jogo->texturas.texturaCartas;
    DrawTextureRec(textura, carta->coordsSprite, Rectangle2Vector(carta->coordsMesa), WHITE);
    jogo->descarteTopo = carta;
  }
}

/*
TODO: Toda essa lógica seria muito mais fácil se o monte de compras e descarte fossem duas
pilhas separadas, pois assim eu consigo controlar mais facilmente o tamanho de cada pilha
e saber a pilha de compra ficou vazia e eu preciso reiniciar a pilha de descarte
*/

void renderizaEstoque(Jogo *jogo) {
  percorreListaGCirc(jogo->estoque, renderizaCartasEstoque, jogo);

  Vector2 mousePos = GetMousePosition();
  // Verifica o clique na pilha de compra pra virar uma carta
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, jogo->estoqueTopo->coordsMesa)) {
    jogo->estoqueTopo->viradaParaBaixo = false;
    jogo->estoqueTopo->coordsMesa.x = 150;
  }

  // Verifica o clique pra arrastar alguma carta da pilha de descarte
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && jogo->descarteTopo && CheckCollisionPointRec(mousePos, jogo->descarteTopo->coordsMesa)) {
    if (jogo->cartaEmMovimento == NULL) {
      jogo->cartaEmMovimento = jogo->descarteTopo;
      jogo->cartaEmMovimento->posicaoAnterior = Rectangle2Vector(jogo->cartaEmMovimento->coordsMesa);
    }
  }
}


#include "carta.h"
#include "jogo.h"
#include "raylib.h"

void renderizaCartas(void *info, void *jogoVar) {
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
  percorreListaGCirc(jogo->estoque, renderizaCartas, jogo);

  Vector2 mousePos = GetMousePosition();
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, jogo->estoqueTopo->coordsMesa)) {
    jogo->estoqueTopo->viradaParaBaixo = false;
    jogo->estoqueTopo->coordsMesa.x = 150;

    // if (jogo->mouseOffset.x == 0) {
    //   jogo->mouseOffset.x = GetMouseX() - jogo->estoqueTopo->coordsMesa.x;
    //   jogo->mouseOffset.y = GetMouseY() - jogo->estoqueTopo->coordsMesa.y;

    //   // isMousePressed = true; // Também define q o mouse está pressionado. Isso serve pra quando tu desliza o mouse mto rápido e ele "sai" da carta
    // }
  }
}

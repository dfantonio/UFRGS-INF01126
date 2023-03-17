#include "carta.h"
#include "estoque.h"
#include "fundacao.h"
#include "tableau.h"
#include "jogo.h"
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

int main() {
  const int screenWidth = 1400;
  const int screenHeight = 650;

  InitWindow(screenWidth, screenHeight, "Jogo de paci�ncia");

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  Jogo jogo;
  criaCartas(&jogo);

  jogo.texturas.texturaCartas = LoadTexture("resources/playingCards.png");
  jogo.texturas.texturaCartaVerso = LoadTexture("resources/cardBack.png");
  jogo.texturas.texturaSlot = LoadTexture("resources/cardSlot.png");
  jogo.texturas.texturaEstoque = LoadTexture("resources/cardReload.png");

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(DARKBLUE);

    renderizaEstoque(&jogo);
    renderizaFundacao(&jogo);
    renderizaTableau(&jogo);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && jogo.cartaEmMovimento) {
      // Deve verificar se a carta em movimento n�o t� em cima de nenhum slot do tableau ou funda��o
      for (int i = 0; i < 4; i++) {
        Rectangle posicaoFundacao = {FUNDACAO_OFFSET_X + (CARTA_LARGURA * i), FUNDACAO_OFFSET_Y, CARTA_LARGURA, CARTA_ALTURA};
        if (jogo.cartaEmMovimento && CheckCollisionRecs(jogo.cartaEmMovimento->coordsMesa, posicaoFundacao)) {
          verificaMovimentoPFundacao(&jogo, i);
        }
      }

      // Caso n�o tenha acontecido nenhuma movimenta��o, retorna a carta pra sua posi��o original
      if (jogo.cartaEmMovimento) {
        jogo.cartaEmMovimento->coordsMesa.x = jogo.cartaEmMovimento->posicaoAnterior.x;
        jogo.cartaEmMovimento->coordsMesa.y = jogo.cartaEmMovimento->posicaoAnterior.y;
        jogo.cartaEmMovimento = NULL;
      }
      jogo.mouseOffset = Vector2Zero();
    }

    if (jogo.cartaEmMovimento) {
      if (jogo.mouseOffset.x == 0) { // Se n�o houver nenhum offset pro mouse signica que � o primeiro clique detectado
        jogo.mouseOffset.x = GetMouseX() - jogo.descarteTopo->coordsMesa.x;
        jogo.mouseOffset.y = GetMouseY() - jogo.descarteTopo->coordsMesa.y;
      }
      jogo.descarteTopo->coordsMesa.x = GetMouseX() - jogo.mouseOffset.x;
      jogo.descarteTopo->coordsMesa.y = GetMouseY() - jogo.mouseOffset.y;
    }

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

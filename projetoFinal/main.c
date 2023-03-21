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

  InitWindow(screenWidth, screenHeight, "Jogo de paciï¿½ncia");

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  Jogo jogo;
  criaLayoutJogo(&jogo);

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
      // Deve verificar se a carta em movimento nï¿½o tï¿½ em cima de nenhum slot do tableau ou fundaï¿½ï¿½o
      for (int i = 0; i < 4; i++) {
        Rectangle posicaoFundacao = {FUNDACAO_OFFSET_X + (CARTA_LARGURA * i), FUNDACAO_OFFSET_Y, CARTA_LARGURA, CARTA_ALTURA};
        if (jogo.cartaEmMovimento && CheckCollisionRecs(jogo.cartaEmMovimento->coordsMesa, posicaoFundacao)) {
          verificaMovimentoPFundacao(&jogo, i);
        }
      }

      // Caso nï¿½o tenha acontecido nenhuma movimentaï¿½ï¿½o, retorna a carta pra sua posiï¿½ï¿½o original
      if (jogo.cartaEmMovimento) {
        jogo.cartaEmMovimento->coordsMesa.x = jogo.cartaEmMovimento->posicaoAnterior.x;
        jogo.cartaEmMovimento->coordsMesa.y = jogo.cartaEmMovimento->posicaoAnterior.y;
        jogo.cartaEmMovimento = NULL;
      }
      jogo.mouseOffset = Vector2Zero();
    }

    if (jogo.cartaEmMovimento) {
      if (jogo.mouseOffset.x == 0) { // Se não houver nenhum offset pro mouse signica que é o primeiro clique detectado
        jogo.mouseOffset.x = GetMouseX() - jogo.cartaEmMovimento->coordsMesa.x;
        jogo.mouseOffset.y = GetMouseY() - jogo.cartaEmMovimento->coordsMesa.y;
      }
      jogo.cartaEmMovimento->coordsMesa.x = GetMouseX() - jogo.mouseOffset.x;
      jogo.cartaEmMovimento->coordsMesa.y = GetMouseY() - jogo.mouseOffset.y;

      // Renderiza a carta em movimento depois de todas as outras
      renderizaCarta(jogo.cartaEmMovimento, &jogo);
    }

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
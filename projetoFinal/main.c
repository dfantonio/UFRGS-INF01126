#include "carta.h"
#include "estoque.h"
#include "fundacao.h"
#include "jogo.h"
#include "raylib.h"
#include "raymath.h"
#include "tableau.h"
#include <stdlib.h>

int main() {
  const int screenWidth = 1400;
  const int screenHeight = 850;

  InitWindow(screenWidth, screenHeight, "Jogo de paciencia");

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

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && (jogo.cartaEmMovimento || jogo.cartasEmMovimento->ini)) {
      // Deve verificar se a carta em movimento nao ta em cima de nenhum slot do tableau ou fundacao
      for (int i = 0; i < NUM_COLUNAS_FUNDACAO; i++) {
        Rectangle posicaoFundacao = {FUNDACAO_OFFSET_X + (CARTA_LARGURA * i), FUNDACAO_OFFSET_Y, CARTA_LARGURA, CARTA_ALTURA};
        if (jogo.cartaEmMovimento && CheckCollisionRecs(jogo.cartaEmMovimento->coordsMesa, posicaoFundacao))
          verificaMovimentoPFundacao(&jogo, i);

        if (jogo.cartasEmMovimento->ini) {
          Carta *origem = jogo.cartasEmMovimento->ini->info;
          if (jogo.cartasEmMovimento->ini && CheckCollisionRecs(origem->coordsMesa, posicaoFundacao)) {
            jogo.cartaEmMovimento = origem;
            verificaMovimentoPFundacao(&jogo, i);
          }
        }
      }

      for (int i = 0; i < NUM_COLUNAS_TABLEAU; i++) {
        if (jogo.cartaEmMovimento && jogo.filaTableau[i]->fim && CheckCollisionRecs(((Carta *)jogo.filaTableau[i]->fim->info)->coordsMesa, jogo.cartaEmMovimento->coordsMesa))
          verificaMovimentoPTableau(&jogo, i);

        if (jogo.cartasEmMovimento->ini && jogo.filaTableau[i]->fim) { // Se tem uma carta em movimento e se há uma carta virara pra cima na coluna desejada
          Carta *origem = jogo.cartasEmMovimento->ini->info;
          Carta *destino = jogo.filaTableau[i]->fim->info;

          if (jogo.cartasEmMovimento->ini && CheckCollisionRecs(destino->coordsMesa, origem->coordsMesa))
            verificaMovimentoPTableau(&jogo, i);
        }
      }

      // Caso nao tenha acontecido nenhuma movimentacao, retorna a carta pra sua posicao original
      if (jogo.cartaEmMovimento) {
        jogo.cartaEmMovimento->coordsMesa.x = jogo.cartaEmMovimento->posicaoAnterior.x;
        jogo.cartaEmMovimento->coordsMesa.y = jogo.cartaEmMovimento->posicaoAnterior.y;
        jogo.cartaEmMovimento = NULL;
      }
      // Caso nao tenha acontecido nenhuma movimentacao, retorna a carta pra sua posicao original
      if (jogo.cartasEmMovimento)
        while (!vaziaFilaGEnc(jogo.cartasEmMovimento)) {
          Carta *cartaTemp = desenfileiraFilaGEnc(jogo.cartasEmMovimento);
          int colunaTableau = (cartaTemp->posicaoAnterior.x - TABLEAU_OFFSET.x) / CARTA_LARGURA;

          cartaTemp->coordsMesa.x = cartaTemp->posicaoAnterior.x;
          cartaTemp->coordsMesa.y = cartaTemp->posicaoAnterior.y;

          enfileiraFilaGEnc(jogo.filaTableau[colunaTableau], cartaTemp);
        }
      jogo.mouseOffset = Vector2Zero();
    }

    // TODO: Remover a lógica de renderizar cartaEmMovimento quando migrarmos tudo pra fila de cartasEmMovimento
    if (jogo.cartaEmMovimento) {
      if (jogo.mouseOffset.x == 0) { // Se nao houver nenhum offset pro mouse signica que eh o primeiro clique detectado
        jogo.mouseOffset.x = GetMouseX() - jogo.cartaEmMovimento->coordsMesa.x;
        jogo.mouseOffset.y = GetMouseY() - jogo.cartaEmMovimento->coordsMesa.y;
      }
      jogo.cartaEmMovimento->coordsMesa.x = GetMouseX() - jogo.mouseOffset.x;
      jogo.cartaEmMovimento->coordsMesa.y = GetMouseY() - jogo.mouseOffset.y;

      // Renderiza a carta em movimento depois de todas as outras
      renderizaCarta(jogo.cartaEmMovimento, &jogo);
    }

    // Renderiza a fila de cartas em movimento e atualiza as suas posições
    if (jogo.cartasEmMovimento->ini) {
      FilaGEnc *filaAux = criaFilaGEnc();
      Carta *cartaTemp = jogo.cartasEmMovimento->ini->info;
      int i = 0;

      if (jogo.mouseOffset.x == 0) { // Se nao houver nenhum offset pro mouse signica que eh o primeiro clique detectado
        jogo.mouseOffset.x = GetMouseX() - cartaTemp->coordsMesa.x;
        jogo.mouseOffset.y = GetMouseY() - cartaTemp->coordsMesa.y;
      }

      while (!vaziaFilaGEnc(jogo.cartasEmMovimento)) {
        cartaTemp = desenfileiraFilaGEnc(jogo.cartasEmMovimento);

        cartaTemp->coordsMesa.x = GetMouseX() - jogo.mouseOffset.x;
        cartaTemp->coordsMesa.y = GetMouseY() - jogo.mouseOffset.y + TABLEAU_OFFSET_DELTA_Y * i++;

        renderizaCarta(cartaTemp, &jogo);
        enfileiraFilaGEnc(filaAux, cartaTemp);
      }

      while (!vaziaFilaGEnc(filaAux))
        enfileiraFilaGEnc(jogo.cartasEmMovimento, desenfileiraFilaGEnc(filaAux));

      destroiFilaGEnc(filaAux);
    }

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
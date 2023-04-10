#include "carta.h"
#include "estoque.h"
#include "fundacao.h"
#include "jogo.h"
#include "raylib.h"
#include "raymath.h"
#include "tableau.h"
#include "menu.h"
#include <stdlib.h>

int main() {
  const int screenWidth = 1400;
  const int screenHeight = 850;

  InitWindow(screenWidth, screenHeight, "Jogo de paciencia");

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  Jogo jogo;
  criaLayoutJogo(&jogo);
  Menu menu;
  inicializaMenu(&menu);

  jogo.texturas.texturaCartas = LoadTexture("resources/playingCards.png");
  jogo.texturas.texturaCartaVerso = LoadTexture("resources/cardBack.png");
  jogo.texturas.texturaSlot = LoadTexture("resources/cardSlot.png");
  jogo.texturas.texturaEstoque = LoadTexture("resources/cardReload.png");

  while (!WindowShouldClose()) {
    BeginDrawing();

    if(IsKeyPressed(KEY_SPACE))
      menu.isOpen = !menu.isOpen;
    if(menu.isOpen)
      renderizaMenu(&menu, &jogo);
    else{
      SetExitKey(KEY_ESCAPE);
      ClearBackground(DARKBLUE);
      renderizaEstoque(&jogo);
      renderizaFundacao(&jogo);
      renderizaTableau(&jogo);

      if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && inicioListaMovimento(&jogo)) {
        Carta *origem = inicioListaMovimento(&jogo);

        // Deve verificar se a carta em movimento nao ta em cima de nenhum slot do tableau ou fundacao
        for (int i = 0; i < NUM_COLUNAS_FUNDACAO; i++) {
          Rectangle posicaoFundacao = {FUNDACAO_OFFSET_X + (CARTA_LARGURA * i), FUNDACAO_OFFSET_Y, CARTA_LARGURA, CARTA_ALTURA};
          if (CheckCollisionRecs(origem->coordsMesa, posicaoFundacao)) {
            verificaMovimentoPFundacao(&jogo, i);
          }
        }

        for (int i = 0; i < NUM_COLUNAS_TABLEAU; i++) {
          if (jogo.filaTableau[i]->fim) { // Se ha uma carta virada pra cima na coluna desejada
            Carta *destino = jogo.filaTableau[i]->fim->info;

            if (CheckCollisionRecs(destino->coordsMesa, origem->coordsMesa)) // Se houve sobreposicao da carta virada pra cima e da carta em movimento
              verificaMovimentoPTableau(&jogo, i);
          } else {
            Rectangle slot = {
                TABLEAU_OFFSET_X + (CARTA_LARGURA * i),
                TABLEAU_OFFSET_Y,
                CARTA_LARGURA,
                CARTA_ALTURA};
            if (CheckCollisionRecs(slot, origem->coordsMesa)) // Se houve sobreposicao da carta virada pra cima e da carta em movimento
              verificaMovimentoPTableau(&jogo, i);
          }
        }

        // Caso nao tenha acontecido nenhuma movimentacao, retorna a carta pra sua posicao original
        while (!vaziaFilaGEnc(jogo.cartasEmMovimento)) {
          Carta *cartaTemp = desenfileiraFilaGEnc(jogo.cartasEmMovimento);
          int colunaTableau = calculaIndiceTableau(cartaTemp);
          int colunaFundacao = calculaIndiceFundacao(cartaTemp);

          cartaTemp->coordsMesa.x = cartaTemp->posicaoAnterior.x;
          cartaTemp->coordsMesa.y = cartaTemp->posicaoAnterior.y;

          switch (cartaTemp->posicao) {
          case FUNDACAO:
            empilhaPilhaGEnc(jogo.fundacao[colunaFundacao], cartaTemp);
            break;

          case TABLEAU:
            enfileiraFilaGEnc(jogo.filaTableau[colunaTableau], cartaTemp);
            break;

          case ESTOQUE:
            empilhaPilhaGEnc(jogo.descarte, cartaTemp);
            break;
          }
        }
        jogo.mouseOffset = Vector2Zero();
      }

      // Renderiza a fila de cartas em movimento e atualiza as suas posicoes
      if (inicioListaMovimento(&jogo)) {
        FilaGEnc *filaAux = criaFilaGEnc();
        Carta *cartaTemp = inicioListaMovimento(&jogo);
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
    }
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
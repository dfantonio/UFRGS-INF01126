
#include "carta.h"
#include "jogo.h"
#include "tableau.h"
#include "raylib.h"
#include <stdlib.h>

void renderizaCartasTableau(void *info, void *jogoVar) {
  Carta *carta = (Carta *)info;
  Jogo *jogo = (Jogo *)jogoVar;
  
  // Caso a carta renderizada nao seja a que esta em movimento
  if (jogo->cartaEmMovimento != carta)
    renderizaCarta(info, jogoVar);
}

void renderizaTableau(Jogo *jogo) {
  Vector2 mousePos = GetMousePosition();
    
  for (int i = 0; i < NUM_COLUNAS_TABLEAU; i++) {
    DrawTexture(jogo->texturas.texturaSlot, TABLEAU_OFFSET_X + (CARTA_LARGURA * i), TABLEAU_OFFSET_Y, WHITE);
    // Percorre todas as pilhas e renderiza as cartas
    percorrePilhaReversoGEnc(jogo->pilhaTableau[i], renderizaCartasTableau, jogo);
    percorreFilaGEnc(jogo->filaTableau[i], renderizaCartasTableau, jogo);
    // Caso a pilha esteja vazia nao verifica movimento
    if (jogo->pilhaTableau[i]->topo) {
      Carta *cartaTopo = jogo->filaTableau[i]->ini->info;
      // Verifica momento pra trocar uma carta entre as colunas do tableau
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cartaTopo && CheckCollisionPointRec(mousePos, cartaTopo->coordsMesa)) {
        if (jogo->cartaEmMovimento == NULL) {
          jogo->cartaEmMovimento = cartaTopo;
          jogo->cartaEmMovimento->posicaoAnterior = Rectangle2Vector(jogo->cartaEmMovimento->coordsMesa);
        }
      }
    }
  }
}

void movimentaCarta(Jogo *jogo, int index) {
  Vector2 mousePos = GetMousePosition();
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && jogo->pilhaTableau[index] && CheckCollisionPointRec(mousePos, jogo->descarteTopo->coordsMesa)) {
    if (jogo->cartaEmMovimento == NULL) {
      jogo->cartaEmMovimento = jogo->descarteTopo;
      jogo->cartaEmMovimento->posicaoAnterior = Rectangle2Vector(jogo->cartaEmMovimento->coordsMesa);
    }
  }
}
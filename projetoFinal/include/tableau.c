
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

void verificaMovimentoPTableau(Jogo *jogo, int index) {
  // Caso a carta venha do estoque
  if (jogo->cartaEmMovimento && jogo->cartaEmMovimento->posicao == ESTOQUE) {
    int numero = 0;
    Carta *ultimaCartaColuna = (Carta *)jogo->filaTableau[index]->fim->info;
    if (jogo->filaTableau[index]->fim) numero = ultimaCartaColuna->numero;

    // Comentei algumas regras pra poder testar
    // // Se a carta nao for 1 numero maior do q o topo da pilha
    // if (jogo->cartaEmMovimento->numero != (numero + 1)) return;
    // // Se os naipes forem diferentes cancela o movimento
    // if (jogo->fundacao[index]->topo && ((Carta *)jogo->fundacao[index]->topo->info)->naipe != jogo->cartaEmMovimento->naipe) return;

    // Move a carta pra fila do tableau
    enfileiraFilaGEnc(jogo->filaTableau[index], jogo->cartaEmMovimento);

    // Arruma as informacoes de posicao da carta
    jogo->cartaEmMovimento->coordsMesa.x = ultimaCartaColuna->coordsMesa.x;
    jogo->cartaEmMovimento->coordsMesa.y = ultimaCartaColuna->coordsMesa.y + TABLEAU_OFFSET_DELTA_Y;
    jogo->cartaEmMovimento->posicao = TABLEAU;

  // Remove a carta da pilha do estoque
    desempilhaPilhaGEnc(jogo->descarte);

    // Finaliza o movimento
    jogo->cartaEmMovimento = NULL;
  }
}
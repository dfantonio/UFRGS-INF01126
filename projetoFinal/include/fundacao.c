#include "carta.h"
#include "jogo.h"
#include "pilha.h"
#include <stdlib.h>

void renderizaCartasFundacao(void *info, void *jogoVar) {
  Carta *carta = (Carta *)info;
  Jogo *jogo = (Jogo *)jogoVar;

  // Caso a carta renderizada n�o seja a que est� em movimento
  if (jogo->cartaEmMovimento != carta)
    renderizaCarta(info, jogoVar);
}

void renderizaFundacao(Jogo *jogo) {
  Vector2 mousePos = GetMousePosition();

  for (int i = 0; i < 4; i++) {
    // Desenha os slots da funca��o
    DrawTexture(jogo->texturas.texturaSlot, FUNDACAO_OFFSET_X + (CARTA_LARGURA * i), FUNDACAO_OFFSET_Y, WHITE);
    // Percorre todas as pilhas e renderiza as cartas
    percorrePilhaReversoGEnc(jogo->fundacao[i], renderizaCartasFundacao, jogo);

    // Caso a pilha esteja vazia n�o verifica movimento
    if (jogo->fundacao[i]->topo) {
      Carta *cartaTopo = jogo->fundacao[i]->topo->info;

      // Verifica momento pra trocar uma carta entre as funda��es
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cartaTopo && CheckCollisionPointRec(mousePos, cartaTopo->coordsMesa)) {
        if (jogo->cartaEmMovimento == NULL) {
          jogo->cartaEmMovimento = cartaTopo;
          jogo->cartaEmMovimento->posicaoAnterior = Rectangle2Vector(jogo->cartaEmMovimento->coordsMesa);
        }
      }
    }
  }
}

void verificaMovimentoPFundacao(Jogo *jogo, int index) {
  // Caso a carta venha do estoque
  if (jogo->cartaEmMovimento && jogo->cartaEmMovimento->posicao == ESTOQUE) {
    int numero = 0;
    if (jogo->fundacao[index]->topo) numero = ((Carta *)jogo->fundacao[index]->topo->info)->numero;

    // Comentei algumas regras pra poder testar
    // // Se a carta n�o for 1 n�mero maior do q o topo da pilha
    // if (jogo->cartaEmMovimento->numero != (numero + 1)) return;
    // // Se os naipes forem diferentes cancela o movimento
    // if (jogo->fundacao[index]->topo && ((Carta *)jogo->fundacao[index]->topo->info)->naipe != jogo->cartaEmMovimento->naipe) return;

    // Move a carta pra pilha da funda��o
    empilhaPilhaGEnc(jogo->fundacao[index], jogo->cartaEmMovimento);

    // Arruma as informa��es de posi��o da carta
    jogo->cartaEmMovimento->coordsMesa.x = FUNDACAO_OFFSET_X + (CARTA_LARGURA * index);
    jogo->cartaEmMovimento->coordsMesa.y = FUNDACAO_OFFSET_Y;
    jogo->cartaEmMovimento->posicao = FUNDACAO;

    // Remove a carta da pilha do estoque
    desempilhaPilhaGEnc(jogo->descarte);

    // Finaliza o movimento
    jogo->cartaEmMovimento = NULL;
  }

  // Caso a carta venha da funda��o
  if (jogo->cartaEmMovimento && jogo->cartaEmMovimento->posicao == FUNDACAO) {
    // S� troca a pilha se for um �s
    if (jogo->cartaEmMovimento->numero != 1) return;

    int indexOrigem = (jogo->cartaEmMovimento->posicaoAnterior.x - FUNDACAO_OFFSET_X) / CARTA_LARGURA;

    // Se j� tiver uma carta naquela funda��o
    if (jogo->fundacao[index]->topo != NULL) return;

    // Move a carta pra nova pilha
    empilhaPilhaGEnc(jogo->fundacao[index], jogo->cartaEmMovimento);

    // Arruma as informa��es de posi��o da carta
    jogo->cartaEmMovimento->coordsMesa.x = FUNDACAO_OFFSET_X + (CARTA_LARGURA * index);
    jogo->cartaEmMovimento->coordsMesa.y = FUNDACAO_OFFSET_Y;
    jogo->cartaEmMovimento->posicao = FUNDACAO;

    // Remove a carta da funda��o antiga
    desempilhaPilhaGEnc(jogo->fundacao[indexOrigem]);

    // Finaliza o movimento
    jogo->cartaEmMovimento = NULL;
  }
}
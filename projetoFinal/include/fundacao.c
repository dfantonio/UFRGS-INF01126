#include "jogo.h"
#include "pilha.h"
#include <stdlib.h>

void renderizaCartasFundacao(void *info, void *jogoVar) {
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

void renderizaFundacao(Jogo *jogo) {
  for (int i = 0; i < 4; i++) {
    // Desenha os slots da funcação
    DrawTexture(jogo->texturas.texturaSlot, FUNDACAO_OFFSET_X + (CARTA_LARGURA * i), FUNDACAO_OFFSET_Y, WHITE);
    // Percorre todas as pilhas e renderiza as cartas
    percorrePilhaGEnc(jogo->fundacao[i], renderizaCartasFundacao, jogo);
  }
}

void verificaMovimentoPFundacao(Jogo *jogo, int index) {
  // Caso a carta venha do estoque
  if (jogo->cartaEmMovimento->posicao == ESTOQUE) {
    int numero = 0;
    if (jogo->fundacao[index]->topo) numero = ((Carta *)jogo->fundacao[index]->topo->info)->numero;

    // Se a carta não for 1 número maior do q o topo da pilha
    if (jogo->cartaEmMovimento->numero != (numero + 1)) return;
    // Se os naipes forem diferentes cancela o movimento
    if (jogo->fundacao[index]->topo && ((Carta *)jogo->fundacao[index]->topo->info)->naipe != jogo->cartaEmMovimento->naipe) return;

    // Move a carta pra pilha da fundação
    empilhaPilhaGEnc(jogo->fundacao[index], jogo->cartaEmMovimento);

    // Arruma as informações de posição da carta
    jogo->cartaEmMovimento->coordsMesa.x = FUNDACAO_OFFSET_X + (CARTA_LARGURA * index);
    jogo->cartaEmMovimento->coordsMesa.y = FUNDACAO_OFFSET_Y;
    jogo->cartaEmMovimento->posicao = FUNDACAO;

    // TODO: Remover a carta da pilha do estoque

    // Finaliza o movimento
    jogo->cartaEmMovimento = NULL;
  }
}

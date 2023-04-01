#include "carta.h"
#include "jogo.h"
#include "pilha.h"
#include "tableau.h"
#include <stdlib.h>

void renderizaCartasFundacao(void *info, void *jogoVar);
bool isProximaDaPilha(Carta *cartaEmMovimento, Carta *ultimaCartaPilha);
bool isMesmoNaipe(Carta *cartaEmMovimento, Carta *ultimaCartaPilha);
bool isNumeroDaCartaProximoDaPilha(Carta *cartaEmMovimento, Carta *ultimaCartaPilha);
bool isUm(int numeroCarta);
bool podePosicionarFundacao(Jogo *jogo, int index);

void renderizaCartasFundacao(void *info, void *jogoVar) {
  Carta *carta = (Carta *)info;
  Jogo *jogo = (Jogo *)jogoVar;

  // Caso a carta renderizada nao seja a que esta em movimento

  if (jogo->cartaEmMovimento != carta)
    renderizaCarta(info, jogoVar);
}

void renderizaFundacao(Jogo *jogo) {
  Vector2 mousePos = GetMousePosition();

  for (int i = 0; i < NUM_COLUNAS_FUNDACAO; i++) {
    // Desenha os slots da fundacao
    DrawTexture(jogo->texturas.texturaSlot, FUNDACAO_OFFSET_X + (CARTA_LARGURA * i), FUNDACAO_OFFSET_Y, WHITE);
    // Percorre todas as pilhas e renderiza as cartas
    percorrePilhaReversoGEnc(jogo->fundacao[i], renderizaCartasFundacao, jogo);

    // Caso a pilha esteja vazia nao verifica movimento
    if (jogo->fundacao[i]->topo) {
      Carta *cartaTopo = jogo->fundacao[i]->topo->info;

      // Verifica momento pra trocar uma carta entre as fundacoes
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cartaTopo && CheckCollisionPointRec(mousePos, cartaTopo->coordsMesa)) {
        if (jogo->cartaEmMovimento == NULL) {
          jogo->cartaEmMovimento = cartaTopo;
          jogo->cartaEmMovimento->posicaoAnterior = Rectangle2Vector(jogo->cartaEmMovimento->coordsMesa);
        }
      }
    }
  }
}

void verificaMovimentoPFundacao(Jogo *jogo, int indexDestino) {
  if (jogo->cartaEmMovimento == NULL) return;
  if(!podePosicionarFundacao(jogo, indexDestino)) return;
  // Move a carta pra pilha da fundacao
  empilhaPilhaGEnc(jogo->fundacao[indexDestino], jogo->cartaEmMovimento);

  // Arruma as informacoes de posicao da carta
  jogo->cartaEmMovimento->coordsMesa.x = FUNDACAO_OFFSET_X + (CARTA_LARGURA * indexDestino);
  jogo->cartaEmMovimento->coordsMesa.y = FUNDACAO_OFFSET_Y;

  if(isOrigemCartaEstoque(jogo->cartaEmMovimento->posicao)) // Remove a carta da pilha do estoque
    desempilhaPilhaGEnc(jogo->descarte);
  else {
    int indexOrigem = (jogo->cartaEmMovimento->posicaoAnterior.x - FUNDACAO_OFFSET_X) / CARTA_LARGURA;
    if (isOrigemCartaFundacao(jogo->cartaEmMovimento->posicao)) // Remove a carta da fundacao antiga
      desempilhaPilhaGEnc(jogo->fundacao[indexOrigem]);
    else if(isOrigemCartaTableau(jogo->cartaEmMovimento->posicao)) {
      jogo->cartaEmMovimento->posicao = FUNDACAO;
      desenfileiraFilaGEnc(jogo->filaTableau[indexOrigem]);
      if(vaziaFilaGEnc(jogo->filaTableau[indexOrigem]))
        viraCartaTableauPilhaParaFila(jogo, indexOrigem);
      }
  }
  jogo->cartaEmMovimento->posicao = FUNDACAO;

  // Finaliza o movimento
  jogo->cartaEmMovimento = NULL;
}

bool podePosicionarFundacao(Jogo *jogo, int index) {
  Carta *cartaEmMovimento = jogo->cartaEmMovimento;
  Carta *ultimaCartaFundacao = NULL;
  if(jogo->fundacao[index]->topo)
    ultimaCartaFundacao = (Carta *)jogo->fundacao[index]->topo->info;
  return (
    (vaziaPilhaGEnc(jogo->fundacao[index]) && isUm(jogo->cartaEmMovimento->numero)) || 
    (isProximaDaPilha(cartaEmMovimento, ultimaCartaFundacao))
  );
}

bool isUm(int numeroCarta) {
  return numeroCarta == 1;
}

bool isNumeroDaCartaProximoDaPilha(Carta *cartaEmMovimento, Carta *ultimaCartaPilha) {
  int numUltimaCartaPilha = 0;
  if (ultimaCartaPilha) 
    numUltimaCartaPilha = ultimaCartaPilha->numero;
  return cartaEmMovimento->numero == (numUltimaCartaPilha + 1);
}

bool isMesmoNaipe(Carta *cartaEmMovimento, Carta *ultimaCartaPilha) {
  return cartaEmMovimento->naipe == ultimaCartaPilha->naipe;
}

bool isProximaDaPilha(Carta *cartaEmMovimento, Carta *ultimaCartaPilha) {
  return (
    isNumeroDaCartaProximoDaPilha(cartaEmMovimento, ultimaCartaPilha) && isMesmoNaipe(cartaEmMovimento, ultimaCartaPilha)
  ); 
}
  
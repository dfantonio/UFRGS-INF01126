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
bool isFilaComApenasUmaCarta(FilaGEnc *fila);
int calculaIndiceFundacao(Carta *carta);

void renderizaCartasFundacao(void *info, void *jogoVar) {
  Carta *carta = (Carta *)info;
  Jogo *jogo = (Jogo *)jogoVar;

  // Caso a carta renderizada nao seja a que esta em movimento

  if (inicioListaMovimento(jogo) != carta)
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

      // Verifica movimento pra trocar uma carta entre as fundacoes
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cartaTopo && CheckCollisionPointRec(mousePos, cartaTopo->coordsMesa)) {
        if (!inicioListaMovimento(jogo)) {
          enfileiraFilaGEnc(jogo->cartasEmMovimento, cartaTopo);
          Carta *topo = inicioListaMovimento(jogo);
          topo->posicaoAnterior = Rectangle2Vector(topo->coordsMesa);
        }
      }
    }
  }
}

void verificaMovimentoPFundacao(Jogo *jogo, int indexDestino) {
  if (!inicioListaMovimento(jogo)) return;
  if (!podePosicionarFundacao(jogo, indexDestino)) return;

  Carta *carta = inicioListaMovimento(jogo);

  int colunaFundacaoOrigem = calculaIndiceFundacao(carta);
  int colunaTableauOrigem = (carta->posicaoAnterior.x - TABLEAU_OFFSET.x) / CARTA_LARGURA;

  if (isOrigemCartaTableau(carta->posicao) && !isFilaComApenasUmaCarta(jogo->cartasEmMovimento)) return;
  // Move a carta pra pilha da fundacao
  empilhaPilhaGEnc(jogo->fundacao[indexDestino], carta);

  // Arruma as informacoes de posicao da carta
  carta->coordsMesa.x = FUNDACAO_OFFSET_X + (CARTA_LARGURA * indexDestino);
  carta->coordsMesa.y = FUNDACAO_OFFSET_Y;

  if (isOrigemCartaFundacao(carta->posicao)) { // Remove a carta da fundacao antiga
    desempilhaPilhaGEnc(jogo->fundacao[colunaFundacaoOrigem]);
  } else if (isOrigemCartaTableau(carta->posicao)) {
    viraCartaTableauPilhaParaFilaSeNecessario(jogo, colunaTableauOrigem);
  }
  desenfileiraFilaGEnc(jogo->cartasEmMovimento);

  carta->posicao = FUNDACAO;
}

bool podePosicionarFundacao(Jogo *jogo, int index) {
  Carta *carta = inicioListaMovimento(jogo);
  Carta *ultimaCartaFundacao = NULL;
  if (jogo->fundacao[index]->topo)
    ultimaCartaFundacao = (Carta *)jogo->fundacao[index]->topo->info;
  return (
      (vaziaPilhaGEnc(jogo->fundacao[index]) && isUm(carta->numero)) ||
      (isProximaDaPilha(carta, ultimaCartaFundacao)));
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
      isNumeroDaCartaProximoDaPilha(cartaEmMovimento, ultimaCartaPilha) && isMesmoNaipe(cartaEmMovimento, ultimaCartaPilha));
}

bool isFilaComApenasUmaCarta(FilaGEnc *fila) {
  return fila->ini->info == fila->fim->info;
}

int calculaIndiceFundacao(Carta *carta) {
  return (carta->posicaoAnterior.x - FUNDACAO_OFFSET_X) / CARTA_LARGURA;
}
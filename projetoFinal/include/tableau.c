
#include "tableau.h"
#include "carta.h"
#include "jogo.h"
#include "raylib.h"
#include <stdlib.h>

bool isRei(int numeroCarta);
bool isNumeroDaCartaProximoDaFila(Carta *cartaEmMovimento, Carta *ultimaCartaColuna);
bool isCorDaCartaProximaDaFila(Carta *cartaEmMovimento, Carta *ultimaCartaColuna);
bool isCartasPretas(Carta *carta);
bool isProximaDaFila(Carta *cartaEmMovimento, Carta *ultimaCartaColuna);
bool podePosicionarTableau(Jogo *jogo, int coluna);
void retiraCartaFundacao(Jogo *jogo);

void renderizaCartasTableau(void *info, void *jogoVar) {
  Carta *carta = (Carta *)info;
  Jogo *jogo = (Jogo *)jogoVar;

  // Caso a carta renderizada nao seja a que esta em movimento
  if (vaziaFilaGEnc(jogo->cartasEmMovimento) || jogo->cartasEmMovimento->ini->info != carta)
    renderizaCarta(info, jogoVar);
}

bool detectaClique(void *info, void *jogoVar) {
  Carta *carta = (Carta *)info;
  Jogo *jogo = (Jogo *)jogoVar;
  Vector2 mousePos = GetMousePosition();

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, carta->coordsMesa)) {
    if (vaziaFilaGEnc(jogo->cartasEmMovimento)) { // Caso nao haja cartas em movimento
      carta->posicaoAnterior = Rectangle2Vector(carta->coordsMesa);
      return true;
    }
  }

  return false;
}

void renderizaTableau(Jogo *jogo) {
  for (int i = 0; i < NUM_COLUNAS_TABLEAU; i++) {
    DrawTexture(jogo->texturas.texturaSlot, TABLEAU_OFFSET_X + (CARTA_LARGURA * i), TABLEAU_OFFSET_Y, WHITE);
    // Percorre todas as pilhas e renderiza as cartas
    percorrePilhaReversoGEnc(jogo->pilhaTableau[i], renderizaCartasTableau, jogo);
    percorreFilaGEnc(jogo->filaTableau[i], renderizaCartasTableau, jogo);

    FilaGEnc *filaAux = criaFilaGEnc();

    // Percorre a fila de baixo pra cima e verifica se houve algum clique
    Carta *cartaClicada = percorreFilaReversoGEnc(jogo->filaTableau[i], detectaClique, jogo);
    bool moverParaFila = false;

    // Percorre toda a lista e adiciona as cartas abaixo da cartaClicada para a fila de movimento
    while (!vaziaFilaGEnc(jogo->filaTableau[i])) {
      Carta *cartaTemp = desenfileiraFilaGEnc(jogo->filaTableau[i]);

      if (cartaTemp == cartaClicada) { // Se a carta atual é a que foi clicada
        moverParaFila = true;
      }
      if (moverParaFila) { // Se deve mover pra fila de cartasEmMovimento ou adicionar na filaAux
        enfileiraFilaGEnc(jogo->cartasEmMovimento, cartaTemp);
        cartaTemp->posicaoAnterior = Rectangle2Vector(cartaTemp->coordsMesa);
      } else
        enfileiraFilaGEnc(filaAux, cartaTemp);
    }
    while (!vaziaFilaGEnc(filaAux))
      enfileiraFilaGEnc(jogo->filaTableau[i], desenfileiraFilaGEnc(filaAux));
    destroiFilaGEnc(filaAux);
  }
}

void verificaMovimentoPTableau(Jogo *jogo, int indexDestino) {
  // TODO: Remover essa gambiarra quando migrarmos tudo pra cartasEmMovimento e removermos o cartaEmMovimento
  if (jogo->cartaEmMovimento) enfileiraFilaGEnc(jogo->cartasEmMovimento, jogo->cartaEmMovimento);

  if (vaziaFilaGEnc(jogo->cartasEmMovimento)) return;
  if (!podePosicionarTableau(jogo, indexDestino)) return;

  Carta *cartaMovimento = jogo->cartasEmMovimento->ini->info;

  // inicializa coordenadas
  int xTableau = indexDestino * CARTA_LARGURA + TABLEAU_OFFSET.x;
  int yTableau = TABLEAU_OFFSET_Y;
  Carta *ultimaCartaColuna = (Carta *)jogo->filaTableau[indexDestino]->fim->info;

  if (isProximaDaFila(jogo->cartasEmMovimento->ini->info, ultimaCartaColuna)) {
    // Arruma as informacoes de posicao da carta
    xTableau = ultimaCartaColuna->coordsMesa.x;
    yTableau = ultimaCartaColuna->coordsMesa.y + TABLEAU_OFFSET_DELTA_Y;
  }

  // Move a carta pra fila do tableau
  enfileiraFilaGEnc(jogo->filaTableau[indexDestino], cartaMovimento);
  cartaMovimento->coordsMesa.x = xTableau;
  cartaMovimento->coordsMesa.y = yTableau;

  EstadosCarta posicaoDeOrigem = cartaMovimento->posicao;
  if (isOrigemCartaEstoque(posicaoDeOrigem))
    desempilhaPilhaGEnc(jogo->descarte);
  else if (isOrigemCartaFundacao(posicaoDeOrigem))
    retiraCartaFundacao(jogo);
  else if (isOrigemCartaTableau(posicaoDeOrigem)) {
    int indexOrigem = (cartaMovimento->posicaoAnterior.x - TABLEAU_OFFSET_X) / CARTA_LARGURA;
    cartaMovimento->posicao = TABLEAU;
    viraCartaTableauPilhaParaFilaSeNecessario(jogo, indexOrigem);
  }
  cartaMovimento->posicao = TABLEAU;
  // Finaliza o movimento
  jogo->cartaEmMovimento = NULL;
  desenfileiraFilaGEnc(jogo->cartasEmMovimento);
  while (!vaziaFilaGEnc(jogo->cartasEmMovimento))
    verificaMovimentoPTableau(jogo, indexDestino);
}

bool isRei(int numeroCarta) {
  return numeroCarta == 13;
}

bool isNumeroDaCartaProximoDaFila(Carta *cartaEmMovimento, Carta *ultimaCartaColuna) {
  int numUltimaCartaColuna = 0;
  if (ultimaCartaColuna->numero)
    numUltimaCartaColuna = ultimaCartaColuna->numero;
  return cartaEmMovimento->numero == (numUltimaCartaColuna - 1);
}

bool isCorDaCartaProximaDaFila(Carta *cartaEmMovimento, Carta *ultimaCartaColuna) {
  return (isCartasPretas(cartaEmMovimento) && !isCartasPretas(ultimaCartaColuna)) ||
         (!isCartasPretas(cartaEmMovimento) && isCartasPretas(ultimaCartaColuna));
}

bool isCartasPretas(Carta *carta) {
  return carta->naipe == ESPADAS || carta->naipe == PAUS;
}

bool isProximaDaFila(Carta *cartaEmMovimento, Carta *ultimaCartaColuna) {
  return (
      isNumeroDaCartaProximoDaFila(cartaEmMovimento, ultimaCartaColuna) && isCorDaCartaProximaDaFila(cartaEmMovimento, ultimaCartaColuna));
}

// Quando uma coluna estiver vazia, eh permitido comecar a monta-la colocando um rei (K)
// de qualquer naipe em sua casa OU a carta eh a proxima da fila
bool podePosicionarTableau(Jogo *jogo, int coluna) {
  if (!jogo->filaTableau[coluna]->fim) return false;

  Carta *cartaEmMovimento = jogo->cartasEmMovimento->ini->info;
  Carta *ultimaCartaColuna = (Carta *)jogo->filaTableau[coluna]->fim->info;
  return (
      (vaziaPilhaGEnc(jogo->pilhaTableau[coluna]) && isRei(((Carta *)jogo->cartasEmMovimento->ini->info)->numero)) ||
      (isProximaDaFila(cartaEmMovimento, ultimaCartaColuna)));
}

void retiraCartaFundacao(Jogo *jogo) {
  for (int i = 0; i < NUM_COLUNAS_FUNDACAO; i++) {
    Rectangle posicaoFundacao = {FUNDACAO_OFFSET_X + (CARTA_LARGURA * i), FUNDACAO_OFFSET_Y, CARTA_LARGURA, CARTA_ALTURA};
    Rectangle posicaoAnteriorCarta = {((Carta *)jogo->cartasEmMovimento->ini->info)->posicaoAnterior.x, ((Carta *)jogo->cartasEmMovimento->ini->info)->posicaoAnterior.y, CARTA_LARGURA, CARTA_ALTURA};
    if (CheckCollisionRecs(posicaoAnteriorCarta, posicaoFundacao)) {
      desempilhaPilhaGEnc(jogo->fundacao[i]);
      break;
    }
  }
}

void viraCartaTableauPilhaParaFilaSeNecessario(Jogo *jogo, int indexOrigem) {
  if (vaziaFilaGEnc(jogo->filaTableau[indexOrigem]) && !vaziaPilhaGEnc(jogo->pilhaTableau[indexOrigem])) {
    Carta *cartaTopo = desempilhaPilhaGEnc(jogo->pilhaTableau[indexOrigem]);
    cartaTopo->viradaParaBaixo = false;
    enfileiraFilaGEnc(jogo->filaTableau[indexOrigem], cartaTopo);
  }
}
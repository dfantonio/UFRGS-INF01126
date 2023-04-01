
#include "carta.h"
#include "jogo.h"
#include "tableau.h"
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
    if (vaziaFilaGEnc(jogo->filaTableau[i])) return;
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

void verificaMovimentoPTableau(Jogo *jogo, int indexDestino) {
  if (jogo->cartaEmMovimento == NULL) return;
  if(!podePosicionarTableau(jogo, indexDestino))
    return; 
  
  // inicializa coordenadas
  int xTableau = indexDestino*CARTA_LARGURA + TABLEAU_OFFSET.x;
  int yTableau = TABLEAU_OFFSET_Y;
  Carta *ultimaCartaColuna = (Carta *)jogo->filaTableau[indexDestino]->fim->info;
  
  if(isProximaDaFila(jogo->cartaEmMovimento, ultimaCartaColuna)) {
    // Arruma as informacoes de posicao da carta
    xTableau = ultimaCartaColuna->coordsMesa.x;
    yTableau = ultimaCartaColuna->coordsMesa.y + TABLEAU_OFFSET_DELTA_Y;
  }
  
  // Move a carta pra fila do tableau
  enfileiraFilaGEnc(jogo->filaTableau[indexDestino], jogo->cartaEmMovimento);
  jogo->cartaEmMovimento->coordsMesa.x = xTableau;
  jogo->cartaEmMovimento->coordsMesa.y = yTableau;
  if(isOrigemCartaEstoque(jogo->cartaEmMovimento->posicao))
    desempilhaPilhaGEnc(jogo->descarte);
  else if(isOrigemCartaFundacao(jogo->cartaEmMovimento->posicao))
    retiraCartaFundacao(jogo);
  else if(isOrigemCartaTableau(jogo->cartaEmMovimento->posicao)) {
    int indexOrigem = (jogo->cartaEmMovimento->posicaoAnterior.x - TABLEAU_OFFSET_X) / CARTA_LARGURA;
    jogo->cartaEmMovimento->posicao = TABLEAU;
    desenfileiraFilaGEnc(jogo->filaTableau[indexOrigem]);
    if(vaziaFilaGEnc(jogo->filaTableau[indexOrigem]))
      viraCartaTableauPilhaParaFila(jogo, indexOrigem);
  }
  jogo->cartaEmMovimento->posicao = TABLEAU;
  // Finaliza o movimento
  jogo->cartaEmMovimento = NULL;
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
  return 
    (isCartasPretas(cartaEmMovimento) && !isCartasPretas(ultimaCartaColuna)) ||
    (!isCartasPretas(cartaEmMovimento) && isCartasPretas(ultimaCartaColuna));
}

bool isCartasPretas(Carta *carta) {
  return carta->naipe == ESPADAS || carta->naipe == PAUS;
}

bool isProximaDaFila(Carta *cartaEmMovimento, Carta *ultimaCartaColuna) {
  return (
    isNumeroDaCartaProximoDaFila(cartaEmMovimento, ultimaCartaColuna) && isCorDaCartaProximaDaFila(cartaEmMovimento, ultimaCartaColuna)
  ); 
}

// Quando uma coluna estiver vazia, é permitido começar a montá-la colocando um rei (K) 
// de qualquer naipe em sua casa OU a carta é a próxima da fila
bool podePosicionarTableau(Jogo *jogo, int coluna) {
  Carta *cartaEmMovimento = jogo->cartaEmMovimento;
  Carta *ultimaCartaColuna = (Carta *)jogo->filaTableau[coluna]->fim->info;
  return (
    (vaziaPilhaGEnc(jogo->pilhaTableau[coluna]) && isRei(jogo->cartaEmMovimento->numero)) || 
    (isProximaDaFila(cartaEmMovimento, ultimaCartaColuna))
  );
}

void retiraCartaFundacao(Jogo *jogo) {
  for (int i = 0; i < NUM_COLUNAS_FUNDACAO; i++) {
    Rectangle posicaoFundacao = {FUNDACAO_OFFSET_X + (CARTA_LARGURA * i), FUNDACAO_OFFSET_Y, CARTA_LARGURA, CARTA_ALTURA};
    Rectangle posicaoAnteriorCarta = {jogo->cartaEmMovimento->posicaoAnterior.x, jogo->cartaEmMovimento->posicaoAnterior.y, CARTA_LARGURA, CARTA_ALTURA};
    if (jogo->cartaEmMovimento && CheckCollisionRecs(posicaoAnteriorCarta, posicaoFundacao)) {
      desempilhaPilhaGEnc(jogo->fundacao[i]);
      break;
    }
  }
}

void viraCartaTableauPilhaParaFila(Jogo *jogo, int indexOrigem) {
  FilaGEnc *filaAux = criaFilaGEnc();
  Carta *cartaTopo = desempilhaPilhaGEnc(jogo->pilhaTableau[indexOrigem]);
  cartaTopo->viradaParaBaixo = false;
  enfileiraFilaGEnc(filaAux, cartaTopo);
  while(!vaziaFilaGEnc(jogo->filaTableau[indexOrigem])) {
    enfileiraFilaGEnc(filaAux, desenfileiraFilaGEnc(jogo->filaTableau[indexOrigem]));
  }
  while(!vaziaFilaGEnc(filaAux)) {
    enfileiraFilaGEnc(jogo->filaTableau[indexOrigem], desenfileiraFilaGEnc(filaAux));
  }
  destroiFilaGEnc(filaAux);
}
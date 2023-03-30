
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
bool isOrigemCartaTableauOuEstoque(EstadosCarta posicaoCarta);
bool isOrigemCartaEstoque(EstadosCarta posicaoCarta);
bool isOrigemCartaTableau(EstadosCarta posicaoCarta);

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

void verificaMovimentoPTableau(Jogo *jogo, int coluna) {
  if (jogo->cartaEmMovimento == NULL)
    return;
  if(!isOrigemCartaTableauOuEstoque(jogo->cartaEmMovimento->posicao))
    return;
  if(!podePosicionarTableau(jogo, coluna))
    return; 
  
  // inicializa coordenadas
  int xTableau = coluna*CARTA_LARGURA + TABLEAU_OFFSET.x;
  int yTableau = TABLEAU_OFFSET_Y;
  Carta *ultimaCartaColuna = (Carta *)jogo->filaTableau[coluna]->fim->info;
  
  if(isProximaDaFila(jogo->cartaEmMovimento, ultimaCartaColuna)) {
    // Arruma as informacoes de posicao da carta
    xTableau = ultimaCartaColuna->coordsMesa.x;
    yTableau = ultimaCartaColuna->coordsMesa.y + TABLEAU_OFFSET_DELTA_Y;
  }
  
  // Move a carta pra fila do tableau
  enfileiraFilaGEnc(jogo->filaTableau[coluna], jogo->cartaEmMovimento);
  jogo->cartaEmMovimento->coordsMesa.x = xTableau;
  jogo->cartaEmMovimento->coordsMesa.y = yTableau;
  if(isOrigemCartaEstoque(jogo->cartaEmMovimento->posicao))
    desempilhaPilhaGEnc(jogo->descarte);
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

bool isOrigemCartaTableauOuEstoque(EstadosCarta posicaoCarta) {
  return isOrigemCartaEstoque(posicaoCarta) || isOrigemCartaTableau(posicaoCarta);
}

bool isOrigemCartaEstoque(EstadosCarta posicaoCarta) {
  return posicaoCarta == ESTOQUE;
}

bool isOrigemCartaTableau(EstadosCarta posicaoCarta) {
  return posicaoCarta == TABLEAU;
}
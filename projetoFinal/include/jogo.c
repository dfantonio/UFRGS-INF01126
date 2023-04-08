#include "jogo.h"
#include "carta.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaListasFilasEPilhas(Jogo *jogo);
void embaralhaBaralho(ListaGEnc *listaCartas, NodoLGEnc *temp[]);
bool isUltimaCartaColuna(int atual, int inicial, int coluna);

void criaLayoutJogo(Jogo *jogo) {
  inicializaListasFilasEPilhas(jogo);

  NodoLGEnc *temp[TAMANHO_BARALHO] = {0};

  // Cria um baralho com todas as cartas
  ListaGEnc *listaCartas = criaBaralho();
  embaralhaBaralho(listaCartas, temp);
  int i, j;
  // Atribui as 24 primeiras cartas para o estoque
  for (int i = 0; i < 24; i++) {
    ((Carta *)temp[i]->info)->viradaParaBaixo = true;
    ((Carta *)temp[i]->info)->coordsMesa = ESTOQUE_OFFSET;
    empilhaPilhaGEnc(jogo->estoque, temp[i]->info);
  }

  // Insere as outras 28 cartas no tableau
  int coluna = 1;
  int indiceCartaInicialTableau = 24; // primeira carta a ser inserida no tableau
  for (j = 0; j < NUM_COLUNAS_TABLEAU; j++) {
    for (i = indiceCartaInicialTableau; i < TAMANHO_BARALHO; i++) {
      if ((i - indiceCartaInicialTableau) == coluna) { // o numero de cartas por coluna eh igual ao indice da coluna
        coluna++;
        indiceCartaInicialTableau = i; // for deve inicializar apos a ultima carta inserida
        break;
      }
      ((Carta *)temp[i]->info)->posicao = TABLEAU; // carta esta no tableau
      Rectangle colunasTableau = TABLEAU_OFFSET;
      colunasTableau.x = j * CARTA_LARGURA + TABLEAU_OFFSET.x;                                        // desloca colunas
      colunasTableau.y = (i - indiceCartaInicialTableau) * TABLEAU_OFFSET_DELTA_Y + TABLEAU_OFFSET_Y; // desloca cartas na pilha
      ((Carta *)temp[i]->info)->coordsMesa = colunasTableau;
      if (isUltimaCartaColuna(i, indiceCartaInicialTableau, coluna)) { // ultima carta da coluna fica virada pra cima
        ((Carta *)temp[i]->info)->viradaParaBaixo = false;
        enfileiraFilaGEnc(jogo->filaTableau[j], temp[i]->info);
      } else {
        ((Carta *)temp[i]->info)->viradaParaBaixo = true;
        empilhaPilhaGEnc(jogo->pilhaTableau[j], temp[i]->info);
      }
    }
  }
}

bool isUltimaCartaColuna(int atual, int inicial, int coluna) {
  return (atual - inicial) == (coluna - 1);
}

Vector2 Rectangle2Vector(Rectangle rec) {
  Vector2 vec = {rec.x, rec.y};
  return vec;
}

void inicializaListasFilasEPilhas(Jogo *jogo) {
  // Inicia todas as listas/pilhas
  jogo->estoque = criaPilhaGEnc();
  jogo->descarte = criaPilhaGEnc();
  jogo->cartasEmMovimento = criaFilaGEnc();

  int i;
  for (i = 0; i < NUM_COLUNAS_FUNDACAO; i++)
    jogo->fundacao[i] = criaPilhaGEnc();
  for (i = 0; i < NUM_COLUNAS_TABLEAU; i++) {
    jogo->pilhaTableau[i] = criaPilhaGEnc();
    jogo->filaTableau[i] = criaFilaGEnc();
  }

  jogo->descarteTopo = NULL;
  jogo->estoqueTopo = NULL;
  jogo->cartaEmMovimento = NULL;
  jogo->mouseOffset.x = 0;
  jogo->mouseOffset.y = 0;
}

void embaralhaBaralho(ListaGEnc *listaCartas, NodoLGEnc *temp[]) {
  SetRandomSeed(0);
  // Copia os enderecos pra um array de 52 posicoes
  int i = 0;
  for (NodoLGEnc *pont = listaCartas->prim; i < TAMANHO_BARALHO; pont = pont->prox) {
    temp[i] = pont;
    i++;
  }
  // Embaralha o array
  int random;
  for (i = 0; i < TAMANHO_BARALHO; i++) {
    random = GetRandomValue(0, TAMANHO_BARALHO - 1);
    NodoLGEnc *t = temp[random];
    temp[random] = temp[i];
    temp[i] = t;
  }
}

bool isOrigemCartaEstoque(EstadosCarta posicaoCarta) {
  return posicaoCarta == ESTOQUE;
}

bool isOrigemCartaTableau(EstadosCarta posicaoCarta) {
  return posicaoCarta == TABLEAU;
}

bool isOrigemCartaFundacao(EstadosCarta posicaoCarta) {
  return posicaoCarta == FUNDACAO;
}
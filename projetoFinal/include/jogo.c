#include "jogo.h"
#include "carta.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaListasEPilhas(Jogo *jogo);
void embaralhaBaralho(ListaGEnc *listaCartas, NodoLGEnc *temp[]);
bool isUltimaCartaColuna(int atual, int inicial, int coluna);

void criaLayoutJogo(Jogo *jogo) {
  inicializaListasEPilhas(jogo);

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
  int coluna=1;
  int indiceCartaInicialTableau=24; //primeira carta a ser inserida no tableau
  for(j = 0; j < NUM_COLUNAS_TABLEAU; j++){
    for (i = indiceCartaInicialTableau; i < TAMANHO_BARALHO; i++) {
      if((i-indiceCartaInicialTableau) == coluna){ //o numero de cartas por coluna eh igual ao indice da coluna
        coluna++;
        indiceCartaInicialTableau = i; //for deve inicializar apos a última carta inserida
        break;
      }

      if(isUltimaCartaColuna(i, indiceCartaInicialTableau, coluna)) //ultima carta da coluna fica virada pra cima
        ((Carta *)temp[i]->info)->viradaParaBaixo = false;
      else ((Carta *)temp[i]->info)->viradaParaBaixo = true;
      ((Carta *)temp[i]->info)->posicao = TABLEAU; //carta esta no tableau

      Rectangle colunasTableau = TABLEAU_OFFSET;
      colunasTableau.x = (j+1)*TABLEAU_OFFSET.x; //desloca colunas
      colunasTableau.y = (i-indiceCartaInicialTableau+TABLEAU_OFFSET_DELTA_Y)*TABLEAU_OFFSET.x; //desloca cartas na pilha
      ((Carta *)temp[i]->info)->coordsMesa = colunasTableau;
      empilhaPilhaGEnc(jogo->tableau[j], temp[i]->info);
    }
  }
}

bool isUltimaCartaColuna(int atual, int inicial, int coluna) {
  return (atual-inicial) == (coluna - 1);
}

Vector2 Rectangle2Vector(Rectangle rec) {
  Vector2 vec = {rec.x, rec.y};
  return vec;
}

void inicializaListasEPilhas(Jogo *jogo){
  // Inicia todas as listas/pilhas
  jogo->estoque = criaPilhaGEnc();
  jogo->descarte = criaPilhaGEnc();

  int i;
  for (i = 0; i < NUM_COLUNAS_FUNDACAO; i++)
    jogo->fundacao[i] = criaPilhaGEnc();
  for(i = 0; i < NUM_COLUNAS_TABLEAU; i++)
    jogo->tableau[i] = criaPilhaGEnc();
  
  jogo->descarteTopo = NULL;
  jogo->estoqueTopo = NULL;
  jogo->cartaEmMovimento = NULL;
  jogo->mouseOffset.x = 0;
  jogo->mouseOffset.y = 0;
}

void embaralhaBaralho(ListaGEnc *listaCartas, NodoLGEnc *temp[]){
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
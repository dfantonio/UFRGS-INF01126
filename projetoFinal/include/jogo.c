#include "jogo.h"
#include "carta.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaListasEPilhas(Jogo *jogo);
void embaralhaBaralho(ListaGEnc *listaCartas, NodoLGEnc *temp[]);

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
  int indiceCartaInseridaTableau=24; //primeira carta a ser inserida no tableau
  for(j = 0; j < NUM_COLUNAS_TABLEAU; j++){
    for (i = indiceCartaInseridaTableau; i < TAMANHO_BARALHO; i++) {
      if((i-indiceCartaInseridaTableau) == coluna){ //o numero de cartas por coluna é igual ao indice da coluna
        coluna++;
        indiceCartaInseridaTableau = i; //for deve inicializar após a última carta inserida
        break;
      }
      ((Carta *)temp[i]->info)->viradaParaBaixo = true;
      ((Carta *)temp[i]->info)->posicao = TABLEAU; //carta está no tableau
      empilhaPilhaGEnc(jogo->tableau[j], temp[i]->info);
    }
  }
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
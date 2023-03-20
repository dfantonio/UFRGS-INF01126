#include "jogo.h"
#include "carta.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#define NUM_COLUNAS_TABLEAU 7

void criaCartas(Jogo *jogo) {
  SetRandomSeed(0);

  // Inicia todas as listas/pilhas
  jogo->estoque = criaPilhaGEnc();
  jogo->descarte = criaPilhaGEnc();
  for (int i = 0; i < 4; i++) {
    jogo->fundacao[i] = criaPilhaGEnc();
  }
  jogo->descarteTopo = NULL;
  jogo->estoqueTopo = NULL;
  jogo->cartaEmMovimento = NULL;
  jogo->mouseOffset.x = 0;
  jogo->mouseOffset.y = 0;
  // TODO: Aqui tbm tem que iniciar o tableau e a funda��o

  NodoLGEnc *temp[TAMANHO_BARALHO] = {0};

  // Cria um baralho com todas as cartas
  ListaGEnc *listaCartas = criaBaralho();

  // Copia os endere�os pra um array de 52 posi��es
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

  // Atribui as 24 primeiras cartas para o estoque
  for (i = 0; i < 24; i++) { 
    ((Carta *)temp[i]->info)->viradaParaBaixo = true;
    ((Carta *)temp[i]->info)->coordsMesa = ESTOQUE_OFFSET;

    empilhaPilhaGEnc(jogo->estoque, temp[i]->info); 
  }

  // Insere as outras 28 cartas no tableau
  int coluna=1;
  int indiceCartaInseridaTableau=24; //primeira carta a ser inserida no tableau
  for(int j = 0; j < NUM_COLUNAS_TABLEAU; j++){
    for (i = indiceCartaInseridaTableau; i < TAMANHO_BARALHO; i++) {
      if((i-indiceCartaInseridaTableau) == coluna){ //o numero de cartas por coluna é igual ao indice da coluna
        coluna++;
        indiceCartaInseridaTableau = i; //for deve inicializar após a última carta inserida
        break;
      }
      ((Carta *)temp[i]->info)->viradaParaBaixo = true;
      ((Carta *)temp[i]->info)->posicao = TABLEAU; //carta está no tableau
      // Insere no tableau
      empilhaPilhaGEnc(jogo->tableau[j], temp[i]->info);
    }
  }
}

Vector2 Rectangle2Vector(Rectangle rec) {
  Vector2 vec = {rec.x, rec.y};

  return vec;
}
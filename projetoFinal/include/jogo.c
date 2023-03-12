#include "jogo.h"
#include "carta.h"
#include <stdio.h>
#include <stdlib.h>

void criaCartas(Jogo *jogo) {
  SetRandomSeed(0);

  // Inicia todas as listas/pilhas
  jogo->estoque = criaListaGCirc();
  // TODO: Aqui tbm tem que iniciar o tableau e a fundação

  NodoLGEnc *temp[TAMANHO_BARALHO] = {0};

  // Cria um baralho com todas as cartas
  ListaGEnc *listaCartas = criaBaralho();

  // Copia os endereços pra um array de 52 posições
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
    insereInicioListaGCirc(jogo->estoque, temp[i]->info);
  }

  // Insere as outras cartas no tableau
  for (i = 24; i < TAMANHO_BARALHO; i++) {
    // Insere no tableau
  }
}

Vector2 Rectangle2Vector(Rectangle rec) {
  Vector2 vec = {rec.x, rec.y};

  return vec;
}
#include "carta.h"
#include "fila.h"
#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>

ListaGEnc *criaBaralho() {
  ListaGEnc *baralho = criaListaGEnc();

  Rectangle coordsSprite;
  Rectangle coordsMesa = {0, 0, CARTA_LARGURA, CARTA_ALTURA};
  Vector2 posicaoAnterior = {0, 0};

  for (int naipe = ESPADAS; naipe <= COPAS; naipe++) {
    for (int numero = 1; numero <= 13; numero++) {
      coordsSprite.x = (numero - 1) * CARTA_LARGURA;
      coordsSprite.y = naipe * CARTA_ALTURA;
      coordsSprite.height = CARTA_ALTURA;
      coordsSprite.width = CARTA_LARGURA;

      Carta *carta = (Carta *)malloc(sizeof(Carta));
      *carta = (Carta){
          numero,
          naipe,
          coordsSprite,
          coordsMesa,
          false,
          ESTOQUE,
          posicaoAnterior};
      insereInicioListaGEnc(baralho, carta);
    }
  }

  return baralho;
};

// Como printf nao funciona, acho que pode remover e deixar o callback como argumento msm
void imprimeCartas(void *info) {
  Carta *carta = (Carta *)info;
  printf("naipe: %d, Numero: %d\n", carta->naipe, carta->numero);
}

void percorreBaralho(ListaGEnc *lista) {
  percorreListaGEnc(lista, imprimeCartas);
}

void renderizaCarta(void *info, void *jogoVar) {
  Carta *carta = (Carta *)info;
  Jogo *jogo = (Jogo *)jogoVar;

  Texture2D textura;
  if (carta->viradaParaBaixo) {
    textura = jogo->texturas.texturaCartaVerso;
    DrawTexture(textura, carta->coordsMesa.x, carta->coordsMesa.y, WHITE);
  } else {
    textura = jogo->texturas.texturaCartas;
    DrawTextureRec(textura, carta->coordsSprite, Rectangle2Vector(carta->coordsMesa), WHITE);
  }
}
#include "carta.h"
#include "tad.h"
#include <stdio.h>
#include <stdlib.h>

ListaGEnc *criaBaralho() {
  ListaGEnc *baralho = criaListaGEnc();

  Rectangle coordsSprite;
  Vector2 coordsMesa = {0, 0};

  for (int naipe = ESPADAS; naipe <= COPAS; naipe++) {
    for (int numero = 1; numero <= 13; numero++) {
      coordsSprite.x = (numero - 1) * CARTA_LARGURA;
      coordsSprite.y = naipe * CARTA_ALTURA;
      coordsSprite.height = CARTA_ALTURA;
      coordsSprite.width = CARTA_LARGURA;

      Carta *carta = (Carta *)malloc(sizeof(Carta));
      *carta = (Carta){numero, naipe, coordsSprite, coordsMesa, false};
      insereInicioListaGEnc(baralho, carta);
    }
  }

  return baralho;
};

// Como printf não funciona, acho que pode remover e deixar o callback como argumento msm
void imprimeCartas(void *info) {
  Carta *carta = (Carta *)info;
  printf("naipe: %d, Numero: %d\n", carta->naipe, carta->numero);
}

void percorreBaralho(ListaGEnc *lista) {
  percorreListaGEnc(lista, imprimeCartas);
}

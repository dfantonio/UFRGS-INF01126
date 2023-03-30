#include <stdio.h>

#include "grafo_pla.h"

int main() {
  GrafoPLA* grafo = criaGrafoPLA(6);

  insereArestaGrafoPLA(grafo, 0, 3, 8);
  insereArestaGrafoPLA(grafo, 0, 1, 2);

  insereArestaGrafoPLA(grafo, 1, 4, 9);
  insereArestaGrafoPLA(grafo, 1, 2, 1);

  insereArestaGrafoPLA(grafo, 2, 5, 1);
  insereArestaGrafoPLA(grafo, 2, 4, 9);

  insereArestaGrafoPLA(grafo, 3, 1, 2);

  insereArestaGrafoPLA(grafo, 4, 3, 5);

  insereArestaGrafoPLA(grafo, 5, 4, 3);

  // bellmanFordGrafoPLA(grafo, 0);

  // imprimeGrafoPLA(grafo);

  dijkstraGrafoPLA(grafo, 0, 5);

  // imprimeGrafoPLA(grafo);

  // Melhor implementar uma operacao para acessar essa informacao
  // printf("d(%d,%d) = %.2f\n", 0, 5, grafo->vertices[5].distInicio);

  // imprimeCaminhoMinimoPesadoGrafoPLA(grafo, 0, 5);

  float resultado = caminhoMinimoPesadoComParadaGrafoPLA(grafo, 0, 4, 5);
  printf("\n Distancia com parada: %.0f\n", resultado);

  destroiGrafoPLA(grafo);

  return 0;
}

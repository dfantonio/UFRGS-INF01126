#include "grafo_pla.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#include "fila_enc.h"

// Funcao auxiliar recursiva para o Caminhamento em Profundidade
void visitaNodoDFSGrafoPLA(GrafoPLA *grafo, int chave);
// Funcao auxiliar para Algs. de Caminhamento
void inicializaCaminhamentoGrafoPLA(GrafoPLA *grafo);

// Funcao auxiliar para os Algs. de Dijkstra e Bellman-Ford
void relaxaGrafoPLA(GrafoPLA *grafo, int chave1, int chave2, float custo);
// Funcao auxiliar para Alg. de Dijkstra
int extraiMinimoGrafoPLA(GrafoPLA *grafo);

// Funcao que cria um grafo
GrafoPLA *criaGrafoPLA(int numVertices) {
  int chave;
  GrafoPLA *grafo = (GrafoPLA *)malloc(sizeof(GrafoPLA));
  grafo->vertices = (NoGrafo *)malloc(sizeof(NoGrafo) * numVertices);
  for (chave = 0; chave < numVertices; chave++)
    grafo->vertices[chave].lista = NULL;
  grafo->numVertices = numVertices;
  return grafo;
}

// Funcao que insere uma aresta em um grafo
void insereArestaGrafoPLA(GrafoPLA *grafo, int chave1, int chave2, float custo) {
  ArestaGrafoP *arestaAux = (ArestaGrafoP *)malloc(sizeof(ArestaGrafoP));
  arestaAux->chaveDest = chave2;
  arestaAux->custo = custo;
  arestaAux->prox = grafo->vertices[chave1].lista;
  grafo->vertices[chave1].lista = arestaAux;
  // Em grafos nao-direcionados, ha a insercao da aresta simetrica
}

// Funcao que imprime vertices e arcos
void imprimeGrafoPLA(GrafoPLA *grafo) {
  int chave;
  for (chave = 0; chave < grafo->numVertices; chave++)
    printf("%d : %.2f [%d]\n", chave, grafo->vertices[chave].distInicio, grafo->vertices[chave].pai);
  for (chave = 0; chave < grafo->numVertices; chave++)
    for (ArestaGrafoP *arestaAux = grafo->vertices[chave].lista;
         arestaAux != NULL; arestaAux = arestaAux->prox)
      printf("(%d,%d) : %.2f\n", chave, arestaAux->chaveDest, arestaAux->custo);
}

// Funcao que destroi um grafo
void destroiGrafoPLA(GrafoPLA *grafo) {
  int chave;
  for (chave = 0; chave < grafo->numVertices; chave++) {
    ArestaGrafoP *arestaAux = grafo->vertices[chave].lista;
    while (arestaAux != NULL) {
      ArestaGrafoP *arestaTmp = arestaAux->prox;
      free(arestaAux);
      arestaAux = arestaTmp;
    }
  }
  free(grafo->vertices);
  free(grafo);
}

// Funcao auxiliar para Algs. de Caminhamento
void inicializaCaminhamentoGrafoPLA(GrafoPLA *grafo) {
  int chave;
  grafo->timestamp = 0;
  for (chave = 0; chave < grafo->numVertices; chave++) {
    grafo->vertices[chave].cor = BRANCO;
    grafo->vertices[chave].tEntrada = -1;
    grafo->vertices[chave].tSaida = -1;
    grafo->vertices[chave].pai = -1;
  }
  for (chave = 0; chave < grafo->numVertices; chave++)
    for (ArestaGrafoP *arestaAux = grafo->vertices[chave].lista;
         arestaAux != NULL; arestaAux = arestaAux->prox) {
      arestaAux->tipo = OUTRA;
    }
}

// Funcao auxiliar recursiva para o Caminhamento em Profundidade
void visitaNodoDFSGrafoPLA(GrafoPLA *grafo, int chave) {
  grafo->vertices[chave].cor = CINZA;
  grafo->vertices[chave].tEntrada = grafo->timestamp++;
  for (ArestaGrafoP *arestaAux = grafo->vertices[chave].lista;
       arestaAux != NULL; arestaAux = arestaAux->prox) {
    int chaveAux = arestaAux->chaveDest;
    if (grafo->vertices[chaveAux].cor == BRANCO) {
      grafo->vertices[chaveAux].pai = chave;
      arestaAux->tipo = EXPLORATORIA;
      visitaNodoDFSGrafoPLA(grafo, chaveAux);
    }
  }
  grafo->vertices[chave].cor = PRETO;
  grafo->vertices[chave].tSaida = grafo->timestamp++;
}

// Alg. para Caminhamento em Profundidade
void DFSGrafoPLA(GrafoPLA *grafo, int chaveInicial) {
  inicializaCaminhamentoGrafoPLA(grafo);
  visitaNodoDFSGrafoPLA(grafo, chaveInicial);
}

// Alg. para Caminhamento em Amplitude
void BFSGrafoPLA(GrafoPLA *grafo, int chaveInicial) {
  inicializaCaminhamentoGrafoPLA(grafo);
  FilaEnc *fila = criaFila();
  enfileiraFila(fila, chaveInicial);
  grafo->vertices[chaveInicial].tEntrada = grafo->timestamp++;
  grafo->vertices[chaveInicial].cor = CINZA;
  grafo->vertices[chaveInicial].distInicio = 0;
  while (!vaziaFila(fila)) {
    int chave1 = desenfileiraFila(fila);
    for (ArestaGrafoP *arestaAux = grafo->vertices[chave1].lista;
         arestaAux != NULL; arestaAux = arestaAux->prox) {
      int chave2 = arestaAux->chaveDest;
      if (grafo->vertices[chave2].cor == BRANCO) {
        grafo->vertices[chave2].pai = chave1;
        grafo->vertices[chave2].distInicio = grafo->vertices[chave1].distInicio + 1;
        grafo->vertices[chave2].tEntrada = grafo->timestamp++;
        grafo->vertices[chave2].cor = CINZA;
        arestaAux->tipo = EXPLORATORIA;
        enfileiraFila(fila, chave2);
      }
    }
    grafo->vertices[chave1].cor = PRETO;
    grafo->vertices[chave1].tSaida = grafo->timestamp++;
  }
  destroiFila(fila);
}

// Funcao auxiliar para os Algs. de Dijkstra e Bellman-Ford
void relaxaGrafoPLA(GrafoPLA *grafo, int chave1, int chave2, float custo) {
  if (grafo->vertices[chave2].distInicio > grafo->vertices[chave1].distInicio + custo) {
    grafo->vertices[chave2].distInicio = grafo->vertices[chave1].distInicio + custo;
    grafo->vertices[chave2].pai = chave1;
  }
}

// Alg. de Bellman-Ford. Encontra caminhos mínimos no grafo
void bellmanFordGrafoPLA(GrafoPLA *grafo, int chaveInicial) {
  int chave1, chave2, chave3;
  for (chave1 = 0; chave1 < grafo->numVertices; chave1++) {
    grafo->vertices[chave1].pai = -1;
    grafo->vertices[chave1].distInicio = FLT_MAX;
  }
  grafo->vertices[chaveInicial].distInicio = 0;
  for (int chave1 = 1; chave1 < grafo->numVertices; chave1++) {
    for (int chave2 = 0; chave2 < grafo->numVertices; chave2++) {
      for (ArestaGrafoP *arestaAux = grafo->vertices[chave2].lista;
           arestaAux != NULL; arestaAux = arestaAux->prox) {
        chave3 = arestaAux->chaveDest;
        relaxaGrafoPLA(grafo, chave2, chave3, arestaAux->custo);
      }
    }
  }
}

// Funcao auxiliar para Alg. de Dijkstra
int extraiMinimoGrafoPLA(GrafoPLA *grafo) {
  int chave, chaveMin = -1;
  for (chave = 0; chave < grafo->numVertices; chave++)
    if (grafo->vertices[chave].cor == CINZA)
      if (chaveMin < 0 ||
          grafo->vertices[chave].distInicio < grafo->vertices[chaveMin].distInicio)
        chaveMin = chave;
  return chaveMin;
}

// Alg. de Dijkstra. Encontra caminho mínimo entre origem e destino no grafo
void dijkstraGrafoPLA(GrafoPLA *grafo, int chaveInicial, int chaveFinal) {
  int chave;
  for (chave = 0; chave < grafo->numVertices; chave++) {
    grafo->vertices[chave].pai = -1;
    grafo->vertices[chave].cor = BRANCO;
    grafo->vertices[chave].distInicio = FLT_MAX;
  }
  grafo->vertices[chaveInicial].cor = CINZA;
  grafo->vertices[chaveInicial].distInicio = 0;
  while ((chave = extraiMinimoGrafoPLA(grafo)) != -1) {
    grafo->vertices[chave].cor = PRETO;
    if (chave == chaveFinal)
      break;
    for (ArestaGrafoP *arestaAux = grafo->vertices[chave].lista;
         arestaAux != NULL; arestaAux = arestaAux->prox) {
      if (grafo->vertices[arestaAux->chaveDest].cor != PRETO) {
        relaxaGrafoPLA(grafo, chave, arestaAux->chaveDest, arestaAux->custo);
        grafo->vertices[arestaAux->chaveDest].cor = CINZA;
      }
    }
  }
}

void auxTesteSemCriatividade(GrafoPLA *grafo, int chOri, int chDest) {
  if (grafo->vertices[chDest].pai == chOri) return;

  auxTesteSemCriatividade(grafo, chOri, grafo->vertices[chDest].pai);
  printf("%d-", grafo->vertices[chDest].pai);
}

void imprimeCaminhoMinimoPesadoGrafoPLA(GrafoPLA *grafo, int chOri, int chDest) {
  printf("%d-", chOri);
  auxTesteSemCriatividade(grafo, chOri, chDest);
  printf("%d", chDest);
}

float caminhoMinimoPesadoComParadaGrafoPLA(GrafoPLA *grafo, int chOri, int chInt, int chDest) {
  float distancia;

  dijkstraGrafoPLA(grafo, chOri, chInt);
  distancia = grafo->vertices[chInt].distInicio;
  imprimeCaminhoMinimoPesadoGrafoPLA(grafo, chOri, chInt);

  dijkstraGrafoPLA(grafo, chInt, chDest);
  distancia += grafo->vertices[chDest].distInicio;

  imprimeCaminhoMinimoPesadoGrafoPLA(grafo, chInt, chDest);

  return distancia;
}

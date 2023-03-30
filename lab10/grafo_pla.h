#ifndef _GRAFO_PLA_H_
#define _GRAFO_PLA_H_

typedef enum {
  EXPLORATORIA = 0,
  OUTRA /* Nao Exploratoria */
} tipoAresta;

typedef enum {
  BRANCO = 0, /* Nao Explorado */
  CINZA,      /* Sob Exploracao */
  PRETO       /* Explorado */
} corVertice;

typedef struct arGrafo {
  float custo;           // Custo da aresta pesada!
  int chaveDest;         // Chave do nodo destino
  struct arGrafo *prox;  // Proxima aresta
  tipoAresta tipo;       // Util para DFS e BFS
} ArestaGrafoP;

typedef struct noGrafo {
  ArestaGrafoP *lista;  // Lista de arestas
  corVertice cor;       // Util para DFS e BFS
  int tEntrada;         // Util para DFS e BFS
  int tSaida;           // Util para DFS e BFS
  int pai;              // Util para DFS e BFS
  float distInicio;     // Util para BFS e Caminhos Minimos
} NoGrafo;

typedef struct {
  int numVertices;    // Numero de vertices
  NoGrafo *vertices;  // Vetor de vertices
  int timestamp;      // Util para DFS e BFS
} GrafoPLA;

// Funcao que cria um grafo
GrafoPLA *criaGrafoPLA(int tamanho);

// Funcao que insere uma aresta em um grafo
void insereArestaGrafoPLA(GrafoPLA *grafo, int chave1, int chave2, float custo);

// Funcao que destroi um grafo
void destroiGrafoPLA(GrafoPLA *grafo);

// Funcao que imprime vertices e arcos
void imprimeGrafoPLA(GrafoPLA *grafo);

// Alg. para Caminhamento em Profundidade
void DFSGrafoPLA(GrafoPLA *grafo, int chaveInicial);

// Alg. para Caminhamento em Amplitude
void BFSGrafoPLA(GrafoPLA *grafo, int chaveInicial);

// Alg. de Dijkstra Encontra caminho mínimo entre origem e destino no grafo
void dijkstraGrafoPLA(GrafoPLA *grafo, int chaveInicial, int chaveFinal);

// Alg. de Bellman-Ford. Encontra caminhos mínimos no grafo
void bellmanFordGrafoPLA(GrafoPLA *grafo, int chaveInicial);

void imprimeCaminhoMinimoPesadoGrafoPLA(GrafoPLA *grafo, int chOri, int chDest);

float caminhoMinimoPesadoComParadaGrafoPLA(GrafoPLA *grafo, int chOri, int chInt, int chDest);

#endif

#ifndef _GRAFO_MATRIZ_ADJACENCIAS_H_
#define _GRAFO_MATRIZ_ADJACENCIAS_H_

#define TAM_MAX_NOME 40
#define TAM_MAX_EMAIL 25

typedef struct
{
  int chave;
  char nome[TAM_MAX_NOME];
  char email[TAM_MAX_EMAIL];
} Aluno;

typedef Aluno Info;

typedef struct
{
  Info *infos;       // informacoes dos vertices
  int **adjacencias; // matriz de adjacencias
  int numVertices;   // numero de vertices validos
  int maxVertices;   // numero maximo de vertices
} GrafoMA;

// Funcao que cria um grafo
GrafoMA *criaGrafoMA(int maxVertices);

// Funcao que insere um nodo em um grafo
int insereNodoGrafoMA(GrafoMA *grafo, Info info);

// Funcao que insere uma aresta em um grafo
int insereArestaGrafoMA(GrafoMA *grafo, int chave1, int chave2);

// Funcao que remove uma aresta de um grafo
int removeArestaGrafoMA(GrafoMA *grafo, int chave1, int chave2);

// Funcao que imprime nodos e arestas de um grafo
void imprimeGrafoMA(GrafoMA *grafo);

// Funcao que destroi um grafo
void destroiGrafoMA(GrafoMA *grafo);

int tamanhoGrafoMA(GrafoMA *grafo);
int ordemGrafoMA(GrafoMA *grafo);
int menorGrauGrafoMA(GrafoMA *grafo);
int maiorGrauGrafoMA(GrafoMA *grafo);

#endif

#include <stdio.h>
#include "arvore_binaria.h"
#include <time.h>
#include <stdlib.h>

int main()
{
  srand(1634041364); // Para reproduzir exemplo
  // srand(time(NULL)); // Para valores aleatorios

  // Aqui seriam chamadas as funcoes de inicializacao de infos
  Info info1 = {.chave = 1, .nome = "Fulano de Tal", .email = "fulano@email.com"};
  Info info2 = {.chave = 2, .nome = "Beltrana de Tal", .email = "beltrana@email.com"};
  Info info3 = {.chave = 3, .nome = "Cicrano de Tal", .email = "cicrano@email.com"};
  Info info4 = {.chave = 4, .nome = "Ciclana de Tal", .email = "ciclana@email.com"};
  Info info5 = {.chave = 5, .nome = "Ciclano de Tal", .email = "ciclano@email.com"};

  ArvBinaria *arv;
  arv = criaArvBinaria();

  insereArvBinaria(arv, info4);
  insereArvBinaria(arv, info5);
  insereArvBinaria(arv, info2);

  insereArvBinaria(arv, info3);
  insereArvBinaria(arv, info1);

  Info infoAux = buscaInfoArvBinaria(arv, 4); // infoAux.chave = 4
  infoAux = buscaInfoArvBinaria(arv, 8);      // infoAux.chave = -1

  // removeInfoArvBinaria(arv, 2); // chave = 2 eh nodo de derivacao
  // removeInfoArvBinaria(arv, 5); // chave = 2 eh nodo folha

  imprimeIndentadoArvBinaria(arv);

  printf("profundidade: %d\n", verificaProfundidadeArvBinaria(arv));

  destroiArvBinaria(arv);
  return 0;
}

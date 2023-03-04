#include <stdio.h>
#include "abp.h"

int main()
{

  // Aqui seriam chamadas as funcoes de inicializacao de infos
  Info info1 = {.chave = 1, .nome = "Fulano de Tal", .email = "fulano@email.com"};
  Info info2 = {.chave = 2, .nome = "Beltrana de Tal", .email = "beltrana@email.com"};
  Info info3 = {.chave = 3, .nome = "Cicrano de Tal", .email = "cicrano@email.com"};
  Info info4 = {.chave = 4, .nome = "Ciclana de Tal", .email = "ciclana@email.com"};
  Info info5 = {.chave = 5, .nome = "Ciclano de Tal", .email = "ciclano@email.com"};

  ABP *arv;
  arv = criaABP();

  insereABP(arv, info3);
  insereABP(arv, info5);
  insereABP(arv, info2);

  insereABP(arv, info4);
  insereABP(arv, info1);

  Info infoAux = buscaInfoABP(arv, 4); // infoAux.chave = 4
  infoAux = buscaInfoABP(arv, 8);      // infoAux.chave = -1

  // removeInfoABP(arv, 2); // chave = 2 eh derivacao
  // removeInfoABP(arv, 3); // chave = 2 eh a raiz
  // removeInfoABP(arv, 8); // chave = 2 nao existe

  imprimeABPParentesesAninhados(arv);

  printf("\n\n Maximo: %d\n", maximoABP(arv));
  printf("\n\n Minimo: %d\n", minimoABP(arv));

  imprimeReverso(arv);

  destroiABP(arv);
  return 0;
}

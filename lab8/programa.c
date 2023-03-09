#include <stdio.h>
#include "avl.h"

int main()
{

  // Aqui seriam chamadas as funcoes de inicializacao de infos
  Info info0 = {.chave = 0, .nome = "Fulano de Tal", .email = "fulano@email.com"};
  Info info1 = {.chave = 1, .nome = "Fulano de Tal", .email = "fulano@email.com"};
  Info info2 = {.chave = 2, .nome = "Beltrana de Tal", .email = "beltrana@email.com"};
  Info info3 = {.chave = 3, .nome = "Cicrano de Tal", .email = "cicrano@email.com"};
  Info info4 = {.chave = 4, .nome = "Ciclana de Tal", .email = "ciclana@email.com"};
  Info info5 = {.chave = 5, .nome = "Ciclana de Tal", .email = "ciclana@email.com"};
  Info info6 = {.chave = 6, .nome = "Ciclana de Tal", .email = "ciclana@email.com"};
  Info info7 = {.chave = 7, .nome = "Ciclana de Tal", .email = "ciclana@email.com"};
  Info info8 = {.chave = 8, .nome = "Ciclana de Tal", .email = "ciclana@email.com"};
  Info info9 = {.chave = 9, .nome = "Ciclana de Tal", .email = "ciclana@email.com"};
  Info info10 = {.chave = 10, .nome = "Ciclana de Tal", .email = "ciclana@email.com"};

  AVL *arv;
  arv = criaAVL();

  insereAVL(arv, info5);
  insereAVL(arv, info7);
  insereAVL(arv, info3);

  // insereAVL(arv, info4);
  insereAVL(arv, info2);

  // insereAVL(arv, info8);
  // insereAVL(arv, info6);

  removeInfoAVL(arv, 7); // pensar em como implementar...
  insereAVL(arv, info7);
  // removeInfoAVL(arv, 1); // pensar em como implementar...

  imprimeAVLParentesesAninhados(arv);

  printf("\nTamanho da arvore %d\n\n", tamanhoAVL(arv));
  printf("Numero de folhas: %d\n\n", contaFolhasAVL(arv));

  destroiAVL(arv);
  return 0;
}

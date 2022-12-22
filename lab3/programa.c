#include <stdio.h>
#include <string.h>
#include "lista_enc.h"

int main()
{
  int retorno;
  ListaEnc *listaA, *listaB;
  listaA = criaListaEnc();
  listaB = criaListaEnc();

  // Aqui seriam chamadas as funcoes de inicializacao de nodos
  Info info1 = {1, "Fulano de Tal", "fulano@email.com"};
  Info info2 = {2, "Beltrana de Tal", "beltrana@email.com"};
  Info info3 = {3, "antonio de Tal", "antonio@email.com"};
  Info info4 = {4, "nilo de Tal", "nilo@email.com"};
  Info info5 = {5, "fran de Tal", "fran@email.com"};
  Info teste1 = {6, "Sor", "Sor@gmail.com"};
  Info teste2 = {7, "Junes", "Junes@gmail.com"};

  insereFimListaEnc(listaA, info1);
  insereFimListaEnc(listaA, info2);
  insereFimListaEnc(listaA, info3);
  // insereFimListaEnc(listaA, info4);
  insereFimListaEnc(listaA, info5);

  insereInicioListaEnc(listaB, teste1);
  // insereFimListaEnc(listaB, teste2);
  // insereFimListaEnc(listaB, teste2);

  insereUnicoListaEnc(listaB, teste2);
  insereUnicoListaEnc(listaB, teste2);

  insereOrdenadoLista(listaA, info4);

  concatenaListaEnc(listaA, listaB);

  imprimeListaEnc(listaA);

  destroiListaEnc(listaA);
  destroiListaEnc(listaB);
  return 0;
}

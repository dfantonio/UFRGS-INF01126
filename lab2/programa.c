#include "lista_cont.h"
#include <stdio.h>
#include <string.h>

int main()
{

  int retorno;
  ListaCont listaA, listaB;
  criaListaCont(&listaA);
  criaListaCont(&listaB);

  Info infoAux;
  // Aqui seriam chamadas as funcoes de inicializacao de nodos
  Info info1 = {1, "Fulano de Tal", "fulano@email.com"};
  Info info2 = {2, "Beltrana de Tal", "beltrana@email.com"};
  Info info3 = {3, "Cicrano de Tal", "cicrano@email.com"};
  Info info4 = {4, "Antonio de Tal", "ciclana@email.com"};
  Info info5 = {5, "Thiago de Tal", "ciclano@email.com"};
  Info info6 = {6, "Mayara", "mayara@email.com"};
  Info info7 = {7, "Nilo", "nilo@email.com"};
  Info info8 = {8, "Junes", "junes@email.com"};

  retorno = inserePosListaCont(&listaA, info1, 0);
  retorno = inserePosListaCont(&listaA, info2, 1);
  retorno = inserePosListaCont(&listaA, info3, 2);
  retorno = inserePosListaCont(&listaA, info4, 3);
  retorno = inserePosListaCont(&listaA, info5, 4);

  // Testa item 1:
  // inverteListaCont(listaA, &listaB);
  // imprimeListaCont(listaB);

  // Testa item 2:
  // imprimeListaCont(listaA);

  // infoAux = removeInfoListaCont(&listaA, 1);

  // printf("%d - %s - %s", infoAux.chave, infoAux.nome, infoAux.email);

  // imprimeListaCont(listaA);

  // Testa item 3:
  inserePosListaCont(&listaB, info6, 0);
  inserePosListaCont(&listaB, info7, 1);
  inserePosListaCont(&listaB, info8, 2);

  retorno = concatenaListaCont(listaA, &listaB);
  if (retorno == 0)
    printf("Deu erro");
  else
    imprimeListaCont(listaB);

  return 0;
}

// COMENTE SEU CÓDIGO

#include <stdio.h>
#include <string.h>
#include "fila_enc.h"
#include "pilha_enc.h"

void invertePilhaEnc(PilhaEnc *pilha)
{
  PilhaEnc *temp1, *temp2;
  Info infoAux;

  temp1 = criaPilhaEnc();
  temp2 = criaPilhaEnc();

  while (!vaziaPilhaEnc(pilha))
  {
    infoAux = desempilhaPilhaEnc(pilha);
    empilhaPilhaEnc(temp1, infoAux);
  }

  while (!vaziaPilhaEnc(temp1))
  {
    infoAux = desempilhaPilhaEnc(temp1);
    empilhaPilhaEnc(temp2, infoAux);
  }

  while (!vaziaPilhaEnc(temp2))
  {
    infoAux = desempilhaPilhaEnc(temp2);
    empilhaPilhaEnc(pilha, infoAux);
  }

  destroiPilhaEnc(temp1);
  destroiPilhaEnc(temp2);
}

void invertePilhaFilaEnc(PilhaEnc *pilha)
{
  FilaEnc *temp;
  Info infoAux;

  temp = criaFilaEnc();

  while (!vaziaPilhaEnc(pilha))
  {
    infoAux = desempilhaPilhaEnc(pilha);
    enfileiraFilaEnc(temp, infoAux);
  }

  while (!vaziaFilaEnc(temp))
  {
    infoAux = desenfileiraFilaEnc(temp);
    empilhaPilhaEnc(pilha, infoAux);
  }

  destroiFilaEnc(temp);
}

FilaEnc *copiaInvertidaFilaEnc(FilaEnc *fila)
{
  FilaEnc *filaDestino, *filaTemp;
  PilhaEnc *pilhaTemp1, *pilhaTemp2;
  Info infoAux;

  filaDestino = criaFilaEnc();
  filaTemp = criaFilaEnc();
  pilhaTemp1 = criaPilhaEnc();
  pilhaTemp2 = criaPilhaEnc();

  while (!vaziaFilaEnc(fila))
  {
    infoAux = desenfileiraFilaEnc(fila);

    enfileiraFilaEnc(filaTemp, infoAux);
    empilhaPilhaEnc(pilhaTemp1, infoAux);
  }

  while (!vaziaPilhaEnc(pilhaTemp1))
  {
    infoAux = desempilhaPilhaEnc(pilhaTemp1);

    empilhaPilhaEnc(pilhaTemp2, infoAux);
    enfileiraFilaEnc(filaDestino, infoAux);
  }

  while (!vaziaPilhaEnc(pilhaTemp2))
  {
    infoAux = desempilhaPilhaEnc(pilhaTemp2);

    enfileiraFilaEnc(fila, infoAux);
  }

  destroiFilaEnc(filaTemp);
  destroiPilhaEnc(pilhaTemp1);
  destroiPilhaEnc(pilhaTemp2);
  return filaDestino;
}

int main()
{
  PilhaEnc *pilha;
  pilha = criaPilhaEnc();

  FilaEnc *fila, *fila2;
  fila = criaFilaEnc();

  Info info1 = {1, "Fulano de Tal", "fulano@email.com"};
  Info info2 = {2, "Beltrana de Tal", "beltrana@email.com"};
  Info info3 = {3, "Cicrano de Tal", "cicrano@email.com"};
  Info info4 = {4, "Ciclana de Tal", "ciclana@email.com"};
  Info info5 = {5, "Ciclano de Tal", "ciclano@email.com"};
  Info infoAux;

  printf("\n PILHAS: \n\n");

  empilhaPilhaEnc(pilha, info1);
  empilhaPilhaEnc(pilha, info2);
  empilhaPilhaEnc(pilha, info3);
  empilhaPilhaEnc(pilha, info4);
  empilhaPilhaEnc(pilha, info5);

  // invertePilhaEnc(pilha);
  // invertePilhaFilaEnc(pilha);

  while (!vaziaPilhaEnc(pilha))
  {
    infoAux = desempilhaPilhaEnc(pilha);
    printf("%d | %s (%s)\n", infoAux.matricula, infoAux.nome, infoAux.email);
  }

  destroiPilhaEnc(pilha);

  printf("\n FILA ORIGINAL: \n\n");

  enfileiraFilaEnc(fila, info1);
  enfileiraFilaEnc(fila, info2);
  enfileiraFilaEnc(fila, info3);
  enfileiraFilaEnc(fila, info4);
  enfileiraFilaEnc(fila, info5);

  fila2 = copiaInvertidaFilaEnc(fila);

  while (!vaziaFilaEnc(fila))
  {
    infoAux = desenfileiraFilaEnc(fila);
    printf("%d | %s (%s)\n", infoAux.matricula, infoAux.nome, infoAux.email);
  }
  destroiFilaEnc(fila);

  printf("\n FILA EDITADA: \n\n");

  while (!vaziaFilaEnc(fila2))
  {
    infoAux = desenfileiraFilaEnc(fila2);
    printf("%d | %s (%s)\n", infoAux.matricula, infoAux.nome, infoAux.email);
  }

  return 0;
}

#include <stdio.h>
#include "pontoEletronico.h"

void iniciaPontoEletronico(PontoEletronico *pPonto)
{
  pPonto->horarioRegistro = 0;
  pPonto->tempoTrabalhadoTotal = 0;
};

void registraPonto(PontoEletronico *pPonto, int hora, int minuto)
{
  // Caso seja um registro de início de turno
  if (pPonto->horarioRegistro == 0)
    pPonto->horarioRegistro = hora * 60 + minuto;
  else
  { // Caso seja um ponto de saída de turno
    int horarioAtual = hora * 60 + minuto;
    int tempoTrabalhado = horarioAtual - pPonto->horarioRegistro;

    pPonto->tempoTrabalhadoTotal += tempoTrabalhado;
    pPonto->horarioRegistro = 0;
  }
};

void imprimeTotalTrabalhadoDia(PontoEletronico ponto)
{
  int hora = ponto.tempoTrabalhadoTotal / 60;
  int minuto = ponto.tempoTrabalhadoTotal % 60;

  printf("\nTempo trabalhado foi de %02d:%02d \n", hora, minuto);
};
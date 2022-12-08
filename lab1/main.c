#include <stdio.h>
#include "pontoEletronico.h"

int main()
{
  PontoEletronico pEletronico;
  iniciaPontoEletronico(&pEletronico);

  registraPonto(&pEletronico, 8, 10); // Chegada ao trabalho
  registraPonto(&pEletronico, 12, 0); // Intervalo para almoco

  registraPonto(&pEletronico, 13, 10); // Volta do almoco
  registraPonto(&pEletronico, 17, 20); // Saida do trabalho

  registraPonto(&pEletronico, 20, 5); // Comecou a fazer hora extra
  registraPonto(&pEletronico, 21, 0); // Terminou a hora extra

  imprimeTotalTrabalhadoDia(pEletronico);

  return 0;
}
#include "jogo.h"

#ifndef _TABLEAU_H_
#define _TABLEAU_H_

void renderizaTableau(Jogo *jogo);
void verificaMovimentoPTableau(Jogo *jogo, int index);
void viraCartaTableauPilhaParaFilaSeNecessario(Jogo *jogo, int indexOrigem);

#endif
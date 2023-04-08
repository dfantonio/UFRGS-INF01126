#include "jogo.h"

#ifndef _FUNDACAO_H_
#define _FUNDACAO_H_

void renderizaFundacao(Jogo *jogo);

void verificaMovimentoPFundacao(Jogo *jogo, int indexDestino);

// Calcula de qual fundacao a carta veio
int calculaIndiceFundacao(Carta *carta);

#endif
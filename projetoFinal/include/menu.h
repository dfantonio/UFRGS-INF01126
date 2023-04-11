#include "jogo.h"
#include "raylib.h"
#include <stdlib.h>

#ifndef _MENU_H_
#define _MENU_H_

typedef struct {
  Texture2D texturaMenu;
  bool isOpen;
  bool isClosing;
} Menu;

// Inicializa o menu
void inicializaMenu(Menu *menu);

// Renderiza o menu
void renderizaMenu(Menu *menu, Jogo *jogo);

// Verifica se o jogador clicou em algum botao do menu
void verificaCliqueMenu(Menu *menu, Jogo *jogo);

#endif
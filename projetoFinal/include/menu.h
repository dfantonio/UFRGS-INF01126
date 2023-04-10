#include "raylib.h"
#include "jogo.h"
#include <stdlib.h>

#ifndef _MENU_H_
#define _MENU_H_

typedef struct {
    Texture2D texturaMenu;
    bool isOpen;
} Menu;

void inicializaMenu(Menu *menu);
void renderizaMenu(Menu *menu, Jogo *jogo);

#endif
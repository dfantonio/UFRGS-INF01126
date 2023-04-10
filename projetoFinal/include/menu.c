
#include "raylib.h"
#include "menu.h"
#include "jogo.h"

void inicializaMenu(Menu *menu) {
    Image imagem = LoadImage("resources/menu_back.png");
    Texture2D textura = LoadTextureFromImage(imagem);
    menu->texturaMenu = textura;
    menu->isOpen = false;
}

void renderizaMenu(Menu *menu, Jogo *jogo) {
  DrawTexture(menu->texturaMenu, 200, 200, WHITE);
  SetExitKey(KEY_KP_3);
  if(IsKeyPressed(KEY_KP_1)){
    criaLayoutJogo(jogo);
    menu->isOpen = false;
  }
  else if(IsKeyPressed(KEY_KP_2))
    menu->isOpen = false;
}


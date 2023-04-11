
#include "menu.h"
#include "jogo.h"
#include "raylib.h"

void inicializaMenu(Menu *menu) {
  Image imagem = LoadImage("resources/menu_back.png");
  Texture2D textura = LoadTextureFromImage(imagem);
  menu->texturaMenu = textura;
  menu->isOpen = false;
}

void verificaCliqueMenu(Menu *menu, Jogo *jogo) {
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){375, 360, 310, 40})) { // Se o clique for para reiniciar o jogo
      criaLayoutJogo(jogo);
      menu->isOpen = false;
    }
    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){375, 440, 310, 40})) // Se o clique for para voltar ao jogo
      menu->isOpen = false;
    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){375, 510, 110, 40})) { // Se o clique for para fechar o jogo
      EndDrawing();
      CloseWindow();
    }
  }
}

void renderizaMenu(Menu *menu, Jogo *jogo) {
  DrawTexture(menu->texturaMenu, 200, 200, WHITE);
  verificaCliqueMenu(menu, jogo);
}

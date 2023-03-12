#include "carta.h"
#include "estoque.h"
#include "jogo.h"
#include "raylib.h"
#include "raymath.h"
#include "tad.h"

static void UpdateDrawFrame(void); // Update and draw one frame

int main() {
  const int screenWidth = 1400;
  const int screenHeight = 650;

  InitWindow(screenWidth, screenHeight, "Jogo de paciência");

  Texture2D cartas = LoadTexture("resources/playingCards.png");
  Texture2D cardSlot = LoadTexture("resources/cardSlot.png");

  int frameWidth = 150;  // Sprite one frame rectangle width
  int frameHeight = 200; // Sprite one frame rectangle height

  Rectangle spriteDaCarta = {frameWidth * 0, 0, frameWidth, frameHeight};
  Vector2 posicaoDaCarta = {150, 150};
  Vector2 mouseOffsetOnClick = {0, 0};

  Rectangle testeCoords = {posicaoDaCarta.x, posicaoDaCarta.y, frameWidth, frameHeight};
  bool isMousePressed = false;

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  Vector2 mousePos;

  Jogo jogo;
  criaCartas(&jogo);

  jogo.texturas.texturaCartas = LoadTexture("resources/playingCards.png");
  jogo.texturas.texturaCartaVerso = LoadTexture("resources/cardBack.png");

  while (!WindowShouldClose()) {
    BeginDrawing();

    UpdateDrawFrame();
    DrawTexture(cardSlot, 350, 150, WHITE);
    DrawTextureRec(cartas, spriteDaCarta, posicaoDaCarta, WHITE);

    // Comecei a brincar com arrastar cartas
    mousePos = GetMousePosition();

    testeCoords.x = posicaoDaCarta.x;
    testeCoords.y = posicaoDaCarta.y;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      if (isMousePressed || CheckCollisionPointRec(mousePos, testeCoords)) {

        // Caso o clique tenha sido recem pressionado, vamos calcular o offset do mouse em relação ao canto superior esquerdo
        if (mouseOffsetOnClick.x == 0) {
          mouseOffsetOnClick.x = GetMouseX() - posicaoDaCarta.x;
          mouseOffsetOnClick.y = GetMouseY() - posicaoDaCarta.y;

          isMousePressed = true; // Também define q o mouse está pressionado. Isso serve pra quando tu desliza o mouse mto rápido e ele "sai" da carta
        }

        posicaoDaCarta.x = GetMouseX() - mouseOffsetOnClick.x;
        posicaoDaCarta.y = GetMouseY() - mouseOffsetOnClick.y;
      }
    }

    // Se o mouse for solto reseto o offset
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      mouseOffsetOnClick = Vector2Zero();
      isMousePressed = false;
    }

    // Se apertar R reseta a coordenada da carta
    if (IsKeyPressed(KEY_R)) {
      posicaoDaCarta.x = 150;
      posicaoDaCarta.y = 150;
    }

    renderizaEstoque(&jogo);

    DrawFPS(10, 10);

    EndDrawing();
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void) {
  ClearBackground(DARKBLUE);
}
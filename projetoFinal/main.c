#include "carta.h"
#include "raylib.h"
#include "raymath.h"
#include "tad.h"

static void UpdateDrawFrame(void); // Update and draw one frame

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Jogo de paci�ncia");

  Texture2D cartas = LoadTexture("resources/playingCards.png");

  int frameWidth = 150;  // Sprite one frame rectangle width
  int frameHeight = 200; // Sprite one frame rectangle height

  Rectangle spriteDaCarta = {frameWidth * 0, 0, frameWidth, frameHeight};
  Vector2 posicaoDaCarta = {150, 150};
  Vector2 mouseOffsetOnClick = {0, 0};

  Rectangle testeCoords = {posicaoDaCarta.x, posicaoDaCarta.y, frameWidth, frameHeight};
  bool isMousePressed = false;

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  Vector2 mousePos;

  // Cria estrutura das cartas
  ListaGEnc *listaCartas = criaBaralho();
  percorreBaralho(listaCartas);

  while (!WindowShouldClose()) {
    BeginDrawing();

    UpdateDrawFrame();
    DrawTextureRec(cartas, spriteDaCarta, posicaoDaCarta, WHITE);

    // Comecei a brincar com arrastar cartas
    mousePos = GetMousePosition();

    testeCoords.x = posicaoDaCarta.x;
    testeCoords.y = posicaoDaCarta.y;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      if (isMousePressed || CheckCollisionPointRec(mousePos, testeCoords)) {

        // Caso o clique tenha sido recem pressionado, vamos calcular o offset do mouse em rela��o ao canto superior esquerdo
        if (mouseOffsetOnClick.x == 0) {
          mouseOffsetOnClick.x = GetMouseX() - posicaoDaCarta.x;
          mouseOffsetOnClick.y = GetMouseY() - posicaoDaCarta.y;

          isMousePressed = true; // Tamb�m define q o mouse est� pressionado. Isso serve pra quando tu desliza o mouse mto r�pido e ele "sai" da carta
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
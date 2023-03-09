/*******************************************************************************************
 *
 *   raylib [core] example - Basic 3d example
 *
 *   Welcome to raylib!
 *
 *   To compile example, just press F5.
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. :)
 *
 *   This example has been created using raylib 1.0 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib.h"
#include "tad.h"
#include "teste2.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
Camera camera = {0};
Vector3 cubePosition = {0};

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void); // Update and draw one frame

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Jogo de paciência");

  Texture2D cartas = LoadTexture("resources/playingCards.png");

  int frameWidth = 150;  // Sprite one frame rectangle width
  int frameHeight = 200; // Sprite one frame rectangle height
  int currentFrame = 0;
  int currentLine = 0;

  Rectangle coordDaCarta = {0, 0, frameWidth, frameHeight};
  Vector2 position = {150, 150};

  teste();
  blaaa();

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    UpdateDrawFrame();

    DrawTextureRec(cartas, coordDaCarta, position, WHITE);
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void) {
  // Update
  //----------------------------------------------------------------------------------
  UpdateCamera(&camera);
  //----------------------------------------------------------------------------------

  // Draw
  //----------------------------------------------------------------------------------
  BeginDrawing();

  // ClearBackground(RAYWHITE);
  ClearBackground(DARKBLUE);

  DrawText("This is a raylib TESTEEEE", 10, 40, 20, WHITE);

  DrawFPS(10, 10);

  EndDrawing();
  //----------------------------------------------------------------------------------
}
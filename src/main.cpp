#include "board/board.hpp"
#include <raylib-cpp.hpp>

int main() {
  // Initialization
  int screenWidth = 800;
  int screenHeight = 520;
  Color darkBlue = {44, 44, 127, 255};

  raylib::Color textColor(LIGHTGRAY);
  raylib::Window w(screenWidth, screenHeight, "Snake Game");

  // Create the Board on the stack (no need for new/delete)
  Board board(25, 15);
  SetTargetFPS(60);

  // Main game loop
  while (!w.ShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();

    ClearBackground(darkBlue);

    board.handleInput();
    if (board.getFrameCounter() >= board.moveInterval) {
      board.moveSnake();
      board.resetFrameCounter(); // Reset counter after moving
    } else {
      board.incrementFrameCounter(); // Increment frame counter
    }
    board.render();

    EndDrawing();
  }

  return 0;
}

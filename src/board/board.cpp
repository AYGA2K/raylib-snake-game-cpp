#include "board.hpp"
#include "raylib.h"
#include <string>

void Board::incrementFrameCounter() { frameCounter++; }

void Board::resetFrameCounter() { frameCounter = 0; }

Board::Board(int width, int height) {
  this->width = width;
  this->height = height;
  int boardWidth = width * cellSize;
  int boardHeight = height * cellSize;
  this->offsetX = (GetScreenWidth() - boardWidth) / 2;
  this->offsetY = (GetScreenHeight() - boardHeight) / 2;

  // Initialize grid with EMPTY cells
  grid = vector<vector<int>>(height, vector<int>(width, EMPTY));

  // Place the snake at the center
  placeSnake();

  // Place the first food item
  placeFood();
}

bool Board::isOccupied(const Position &pos) const {
  return grid[pos.y][pos.x] == SNAKE;
}
void Board::reset() {
  // Reset game variables
  gameOver = false;
  score = 0;
  snakeBody.clear();
  snakePositions.clear();

  // Reset the board
  grid = vector<vector<int>>(height, vector<int>(width, EMPTY));

  // Place the snake at the center
  placeSnake();

  // Place the first food item
  placeFood();
}
void Board::updateCell(const Position &pos, CellState state) {
  // Update the grid state for the given position
  grid[pos.y][pos.x] = state;
}

// Place the snake in the middle of the board
void Board::placeSnake() {
  int midX = (width - 1) / 2;  // Horizontal center
  int midY = (height - 1) / 2; // Vertical center

  snakeBody.push_back({midX, midY}); // Head of the snake
  snakeBody.push_back({midX - 1, midY});
  snakeBody.push_back({midX + 1, midY});

  // Set cells to represent the snake's initial position
  updateCell({midX, midY}, SNAKE);
  updateCell({midX - 1, midY}, SNAKE);
  updateCell({midX + 1, midY}, SNAKE);
}

void Board::placeFood() {
  do {
    // Generate random x and y within the bounds of the board
    foodPosition.x = GetRandomValue(0, width - 1);
    foodPosition.y = GetRandomValue(0, height - 1);
  } while (isOccupied(foodPosition));

  // Set the new food position
  updateCell(foodPosition, FOOD);
}

void Board::render() const {
  // Stop rendering the board if the game is over
  if (gameOver) {
    DrawText("Game Over!", GetScreenWidth() / 2 - 150,
             GetScreenHeight() / 2 - 120, 60, RED);

    DrawText(("Score: " + to_string(score)).c_str(), GetScreenWidth() / 2 - 100,
             GetScreenHeight() / 2 - 30, 50, LIGHTGRAY);

    DrawText("Press Enter or Space to Restart", GetScreenWidth() / 2 - 240,
             GetScreenHeight() / 2 + 40, 30, GREEN);
    return;
  }

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      Color color;

      // Determine color based on cell state
      switch (grid[y][x]) {
      case EMPTY:
        color = DARKGRAY;
        break;
      case SNAKE:
        color = GREEN;
        break;
      case FOOD:
        color = RED;
        break;
      default:
        color = DARKGRAY;
        break;
      }

      // Draw each cell as a rectangle with the offset applied
      DrawRectangle(offsetX + x * cellSize, offsetY + y * cellSize, cellSize,
                    cellSize, color);

      //  Draw grid lines for visibility with the offset applied
      DrawRectangleLines(offsetX + x * cellSize, offsetY + y * cellSize,
                         cellSize, cellSize, BLACK);
    }
  }
  DrawText(("Score: " + to_string(score)).c_str(), 10, 10, 20, LIGHTGRAY);
}

void Board::handleInput() {
  if (gameOver) {
    // Check for Enter or Space to reset the game
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
      reset();
    }
    return;
  }

  if (IsKeyPressed(KEY_UP) && snakeDirection != DOWN) {
    snakeDirection = UP;
  } else if (IsKeyPressed(KEY_DOWN) && snakeDirection != UP) {
    snakeDirection = DOWN;
  } else if (IsKeyPressed(KEY_LEFT) && snakeDirection != RIGHT) {
    snakeDirection = LEFT;
  } else if (IsKeyPressed(KEY_RIGHT) && snakeDirection != LEFT) {
    snakeDirection = RIGHT;
  }
}
void Board::moveSnake() {
  if (gameOver)
    return;

  Position newHead = snakeBody.front(); // Get the current head position

  // Update the head’s position based on the direction
  switch (snakeDirection) {
  case UP:
    newHead.y--;
    break;
  case DOWN:
    newHead.y++;
    break;
  case LEFT:
    newHead.x--;
    break;
  case RIGHT:
    newHead.x++;
    break;
  }

  // Check for wall collision (border conditions)
  if (newHead.x < 0 || newHead.x >= width || newHead.y < 0 ||
      newHead.y >= height) {
    gameOver = true;
    return;
  }

  // Check for self-collision
  if (snakePositions.find(newHead) != snakePositions.end()) {
    gameOver = true;
    return;
  }

  bool ateFood = (newHead.x == foodPosition.x && newHead.y == foodPosition.y);

  // Move the snake by adding the new head position
  snakeBody.push_front(newHead);
  snakePositions[newHead] = true;

  // If food was eaten, generate new food; otherwise, remove the tail
  if (ateFood) {
    score++;
    placeFood();
  } else {
    Position tail = snakeBody.back();
    snakeBody.pop_back();
    snakePositions.erase(tail);
    updateCell(tail, EMPTY);
  }

  // Mark the new head position on the grid
  updateCell(newHead, SNAKE);
}

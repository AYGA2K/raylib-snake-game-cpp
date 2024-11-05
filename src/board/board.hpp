#ifndef BOARD_HPP
#define BOARD_HPP

#include <deque>
#include <map>
#include <vector>
using namespace std;

// Position struct to store x and y coordinates
struct Position {
  int x;
  int y;

  // Define comparison operator for Position
  bool operator<(const Position &other) const {
    if (y < other.y) {
      return true;
    } else if (y > other.y) {
      return false;
    } else {
      return x < other.x;
    }
  }

  // Comparison operator for easy position comparison
  bool operator==(const Position &other) const {
    return x == other.x && y == other.y;
  }
};

class Board {
public:
  enum Direction { UP, DOWN, LEFT, RIGHT };
  enum CellState { EMPTY = 0, SNAKE, FOOD };

  // Move every 10 frames
  const int moveInterval = 10;

  Board(int width, int height);

  // Place snake on an empty cells
  void placeSnake();

  // Place food on an empty cell
  void placeFood();

  // Check if position is outside the board
  bool isOutOfBounds(const Position &pos) const;

  // Check if a cell is occupied
  bool isOccupied(const Position &pos) const;

  // Update specific cell state
  void updateCell(const Position &pos, CellState state);

  // Reset board to initial state
  void reset();

  // Render or prepare board for display
  void render() const;

  // Initial direction
  Direction snakeDirection = RIGHT;

  // Store snake body positions as a queue
  deque<Position> snakeBody;

  // Move snake
  void moveSnake();

  // handle user input (arrows) to move the snake
  void handleInput();

  int getWidth() const { return width; }
  int getHeight() const { return height; }
  int getOffsetX() const;
  int getOffsetY() const;
  int getFrameCounter() const { return frameCounter; }
  void resetFrameCounter();
  void incrementFrameCounter();
  int getScore() const { return score; }

private:
  // Board dimensions
  int width, height;
  int offsetX, offsetY;
  int cellSize = 30;
  int padding = 60;
  // 2D grid representing the board
  vector<vector<int>> grid;

  // Current food position
  Position foodPosition;

  // track snake positons
  map<Position, bool> snakePositions;

  int frameCounter = 0;
  int score = 0;
  bool gameOver = false;
};

#endif

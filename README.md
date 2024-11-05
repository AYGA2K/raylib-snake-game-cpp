# Snake Game

This is a classic Snake game implemented in C++ for Linux using the Raylib library. The game features simple graphics and intuitive controls, allowing players to navigate the snake to eat food while avoiding collisions with the walls and itself.

## Features

- **Classic Gameplay**: Navigate the snake to collect food and grow in size.
- **Grid-Based Movement**: The game board is structured as a grid, making movement predictable and straightforward.
- **Collision Detection**: The game detects collisions with walls and the snake's own body to end the game.
- **Dynamic Food Placement**: Food is randomly placed on the board, with checks to avoid placing it where the snake currently is.

## Prerequisites

To run this game on Linux, you need to have the following installed:

- [C++ Compiler](https://gcc.gnu.org/) (e.g., g++, clang)
- [Raylib](https://www.raylib.com/) library for graphics and input handling. Follow the [installation guide](https://raylib.com/).

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/AYGA2K/raylib-snake-game-cpp.git
   cd snake-game
   ```

2. Install Raylib if you haven't done so already. Instructions can be found in the [Raylib documentation](https://raylib.com/).

3. To compile and run the game, use the provided Makefile:
   ```bash
   make
   ```

## Controls

- **Arrow Keys**: Control the direction of the snake (Up, Down, Left, Right).
- **Escape**: Close the game window.

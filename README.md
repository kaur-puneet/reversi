# Reversi (Othello) Game

This repository contains a command-line implementation of the Reversi (Othello) game in C. The game allows two players, a human and a computer, to take turns and compete against each other.

## Files in the Repository

### `reversi_game.c`

- **Author:** Puneet Kaur
- This file contains the main source code for the Reversi game.
- Key functions include:
  - `printBoard`: Prints the current game board.
  - `positionInBounds`: Checks if a given position is within the bounds of the board.
  - `isMoveValid`: Checks if a move is valid for a given player.
  - `checkLegalInDirection`: Checks if a move is legal in a specified direction.
  - `directions`: Generates directional vectors for move validation.
  - `score`: Calculates the score for a move.
  - `flipTheTiles`: Flips the opponent's tiles when a move is made.
  - `compMove`: Handles the computer's move.
  - `humanMove`: Handles the human player's move.
  - `winner`: Determines the winner of the game.
  - `checkGameEnd`: Checks if the game has ended.
  - `main`: The main function that initiates the game.

### `reversi_ai.c`

- **Author:** Puneet Kaur
- This file contains additional functions for move validation and scoring.
- Key functions include:
  - `score`: Calculates the score for a move, considering strategic board positions.
  - `isMoveValid`: Checks if a move is valid for a given player.
  - `checkLegalInDirection`: Checks if a move is legal in a specified direction.
  - `directions`: Generates directional vectors for move validation.
  - `printBoard`: Prints the current game board.
  - `positionInBounds`: Checks if a given position is within the bounds of the board.
  - `makeMove`: Makes a move for the computer player, considering strategic scoring.

## How to Play

1. Run the game file: `reversi_game.c`
2. Follow the on-screen prompts to enter the board dimension and choose the player colors (Black or White).
3. Enter your moves in the format "RowCol" (e.g., "d3"). If it's the computer's turn, it will make a move automatically.
4. Continue playing until the game ends. The winner will be displayed at the end of the game.

## Working of the Game and AI

The Reversi game follows the standard rules of Othello. Players take turns placing their discs on the board and aim to flip their opponent's discs to their color. The game ends when there are no valid moves left for either player or when the board is full.

The AI, implemented in `reversi_ai.c`, enhances the game by making strategic decisions. It assigns scores to moves based on their strategic value, prioritizing corners and edges of the board. The computer's move selection is based on maximizing the score, leading to a more competitive and challenging gaming experience.

Enjoy playing Reversi with this command-line implementation! 

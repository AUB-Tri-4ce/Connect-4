#include "board.h"
#include <stdlib.h>

Board *board_new(Player *players[2]) {
  Board *board = malloc(sizeof(Board)); // allocate
  if (!board) {                         // malloc fail safety check
    return NULL;
  }
  for (int r = 0; r < ROWS; r++) { // initialize the grid
    for (int c = 0; c < COLS; c++) {
      board->grid[r][c] = '.';
    }
  }
  board->players[0] = players[0];
  board->players[1] = players[1];
  board->current_player = 0; // start with player 0

  return board;
}

BoardState board_state(Board *board);

const Player *board_get_current_player(Board *board) {
  return board->players[board->current_player];
}

// maybe use bool to return is the move is allowed
char board_play(Board *board, char column);

Player *board_get_winner(Board *board);

void board_print(Board *board);

void board_free(Board *board) {
  free(board); // only thing to deallocate
}
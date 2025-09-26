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
  board->winner = -1;

  return board;
}

BoardState board_state(Board *board);

const Player *board_get_current_player(Board *board) {
  return board->players[board->current_player];
}

char board_is_move_valid(Board *board, char column) {
  return board->grid[0][column] == '.';
}

// maybe use bool to return is the move is allowed
char board_play(Board *board, char column) {
  Player *curr_player;
  curr_player = board_get_current_player(board);

  if(board->grid[0][column]=='.') {
    for(int row=6; row>=0; row--) {
      if(board->grid[row][column]=='.') {
        board->grid[row][columnn] = curr_player->initial;
        break;
      }
    }
  }
  board_print(board);
const Player *board_get_winner(Board *board) {
  return board->players[board->winner];
}

  if(board->current_player==0)
    board->current_player = 1;
  else board->current_player = 0;
}

const Player *board_get_winner(Board *board) {
  return board->players[board->winner];
}

void board_print(Board *board) {
  for(int row=0; row<ROWS; row++) {
    for(int col=0; col<COLS; col++) {
      printf(" %c",board->grid[row][col]);
    }
    printf('\n');
  }
  for(int col=0; col<COLS; col++) {
    printf("%d ", col);
  }
}

void board_free(Board *board) {
  free(board); // only thing to deallocate
}
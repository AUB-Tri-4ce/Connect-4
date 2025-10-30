#include "board.h"
#include <stdio.h>
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
  board->winner = NULL;

  return board;
}

char board_is_winning_move(Board *board, char column) {
  int row = 0;
  while (board->grid[row][column] == '.')
    row++;

  char playerInitial = board->grid[row][column];

  char steps[4][2] = {{1, -1}, {1, 0}, {1, 1}, {0, 1}};
  for (int i = 0; i < 4; i++) {
    char stepRow = steps[i][1];
    char stepCol = steps[i][0];

    char position_along_axis = -3;
    char currentRow = row + position_along_axis * stepRow;
    char currentCol = column + position_along_axis * stepCol;

    while (currentCol < 0 || currentCol >= COLS || currentRow < 0 ||
           currentRow >= ROWS) {
      currentRow += stepRow;
      currentCol += stepCol;
      position_along_axis++;
    }

    char consecutive = 0;

    while (consecutive < 4 && position_along_axis < 4) {
      if (currentCol < 0 || currentCol >= COLS || currentRow < 0 ||
          currentRow >= ROWS) {
        break;
      }

      if (board->grid[currentRow][currentCol] == playerInitial) {
        consecutive++;
      } else {
        consecutive = 0;
      }

      currentRow += stepRow;
      currentCol += stepCol;
      position_along_axis++;
    }

    if (consecutive == 4)
      return 1;
  }

  return 0;
}

const Player *board_get_current_player(Board *board) {
  return board->players[board->current_player];
}

char board_is_move_valid(Board *board, char column) {
  if (column < 0 || column >= COLS)
    return 0;
  return board->grid[0][column] == '.';
}

BoardState board_play(Board *board, char column) {
  const Player *curr_player = board_get_current_player(board);

  if (board->grid[0][column] == '.') {
    for (int row = ROWS; row >= 0; row--) {
      if (board->grid[row][column] == '.') {
        board->grid[row][column] = curr_player->initial;
        break;
      }
    }
  }

  if (board_is_winning_move(board, column)) {
    board->winner = curr_player;
    board->current_state = BOARD_STATE_WIN;
  } else if (board_is_tie(board)) {
    board->current_state = BOARD_STATE_TIE;
  } else {
    board->current_state = BOARD_STATE_ONGOING;
  }

  board->current_player = 1 - board->current_player;

  return board->current_state;
}

void board_undo(Board *board, char column) {
  for (int row = 0; row < ROWS; row++) {
    if (board->grid[row][column] != '.') {
      board->grid[row][column] = '.';
      break;
    }
  }

  if (board->current_player == 0)
    board->current_player = 1;
  else
    board->current_player = 0;
}

char board_is_tie(Board *board) {
  if (board->winner != NULL)
    return 0;

  for (int i = 0; i < COLS; i++) {
    if (board->grid[0][i] == '.')
      return 0;
  }
  return 1;
}

const Player *board_get_winner(Board *board) { return board->winner; }

void board_print(Board *board) {
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      printf(" %c", board->grid[row][col]);
    }
    printf("\n");
  }
  for (int col = 0; col < COLS; col++) {
    printf(" \e[0;32m%d\e[0m", col);
  }
  printf("\n");
}

void board_free(Board *board) {
  free(board); // only thing to deallocate
}

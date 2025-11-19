#pragma once
#include "player.h"

#define ROWS 6
#define COLS 7

typedef enum {
  BOARD_STATE_ONGOING,
  BOARD_STATE_WIN,
  BOARD_STATE_TIE
} BoardState;

typedef struct {
  char grid[ROWS][COLS];
  const Player *players[2];
  char current_player;
  BoardState current_state;
  const Player *winner;
} Board;

Board *board_new(Player *players[2]);

char board_is_winning_move(Board *board, char column);

const Player *board_get_current_player(Board *board);

char board_is_move_valid(Board *board, char column);

BoardState board_play(Board *board, char column);

void board_undo(Board *board, char column);

char board_is_tie(Board *board);

const Player *board_get_winner(Board *board);

void board_print(Board *board);

void board_copy(Board *source, Board **destination);

void board_free(Board *board);
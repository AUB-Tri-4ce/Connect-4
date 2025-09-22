#pragma once
#include "player.h"

typedef struct
{
  char grid[6][7];
  const Player *players[2];
  char current_player;
} Board;

typedef enum
{
  BOARD_STATE_ONGOING,
  BOARD_STATE_WIN,
  BOARD_STATE_TIE
} BoardState;

Board *board_new(Player *players[2]);

BoardState board_state(Board *board);

Player *board_get_current_player(Board *board);

// maybe use bool to return is the move is allowed
char board_play(Board *board, char column);

Player *board_get_winner(Board *board);

void board_print(Board *board);

void board_free(Board *board);
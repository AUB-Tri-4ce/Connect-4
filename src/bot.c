#include "bot.h"
#include "board.h"
#include <stdlib.h>

char bot_play_easy(Board *board) {
  char col;
  do {
    col = rand() % 7;
  } while (!board_is_move_valid(board, col));

  return col;
}

// char bot_play_moderate(Board *board) {}

// char bot_play_hard(Board *board) {}
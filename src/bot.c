#include "bot.h"
#include "board.h"
#include "player.h"
#include <limits.h>
#include <stdlib.h>

char bot_play_easy(Board *board) {
  char col;
  do {
    col = rand() % 7;
  } while (!board_is_move_valid(board, col));

  return col;
}

int minimax(Board *board, int depth, char is_maximizing_player,
            const Player *maximizing_player) {

  if (depth <= 0)
    return 0;

  if (board->current_state != BOARD_STATE_ONGOING) {
    if (board->current_state == BOARD_STATE_TIE) {
      return 0;
    } else if (board->current_state == BOARD_STATE_WIN) {
      if (board->winner == maximizing_player) {
        return depth;
      } else {
        return -1;
      }
    }
  }

  if (is_maximizing_player) {
    int value = INT_MIN;
    for (int col = 0; col < COLS; col++) {
      if (board_is_move_valid(board, col)) {
        board_play(board, col);
        int m = minimax(board, depth - 1, 0, maximizing_player);
        if (m > value)
          value = m;
        board_undo(board, col);
      }
    }
    return value;
  } else {
    int value = INT_MAX;
    for (int col = 0; col < COLS; col++) {
      if (board_is_move_valid(board, col)) {
        board_play(board, col);
        int m = minimax(board, depth - 1, 1, maximizing_player);
        if (m < value)
          value = m;
        board_undo(board, col);
      }
    }
    return value;
  }
}

char bot_play_moderate(Board *board) {
  int best_score = INT_MIN;
  int best_col = 0;

  const Player *bot_player = board_get_current_player(board);

  for (int col = 0; col < COLS; col++) {
    if (board_is_move_valid(board, col)) {
      board_play(board, col);
      int score = minimax(board, 7, 0, bot_player);
      board_undo(board, col);

      if (score > best_score ||
          (score == best_score &&
           abs((COLS / 2) - col) < ((COLS / 2) - best_col))) {
        best_score = score;
        best_col = col;
      }
    }
  }

  return best_col;
}

// char bot_play_hard(Board *board) {}
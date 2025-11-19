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

int moderate_minimax(Board *board, int depth, char is_maximizing_player,
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
        int m = moderate_minimax(board, depth - 1, 0, maximizing_player);
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
        int m = moderate_minimax(board, depth - 1, 1, maximizing_player);
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
      int score = moderate_minimax(board, 1, 0, bot_player);
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

static int cols_order[COLS] = {};

void generate_cols_order() {
  int mid = COLS / 2;
  int k = 0;

  cols_order[k++] = mid;
  for (int i = 1; i <= mid; i++) {
    if (mid + i < COLS)
      cols_order[k++] = mid + i;
    if (mid - i >= 0)
      cols_order[k++] = mid - i;
  }
}

int hard_minimax(Board *board, int depth, int alpha, int beta,
                 char is_maximizing_player, const Player *maximizing_player) {

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
    for (int col_index = 0; col_index < COLS; col_index++) {
      int col = cols_order[col_index];

      if (board_is_move_valid(board, col)) {
        board_play(board, col);
        int m =
            hard_minimax(board, depth - 1, alpha, beta, 0, maximizing_player);
        if (m > value)
          value = m;

        if (value >= beta) {
          board_undo(board, col);
          break;
        };
        alpha = alpha > value ? alpha : value;
        board_undo(board, col);
      }
    }
    return value;
  } else {
    int value = INT_MAX;
    for (int col_index = 0; col_index < COLS; col_index++) {
      int col = cols_order[col_index];

      if (board_is_move_valid(board, col)) {
        board_play(board, col);
        int m =
            hard_minimax(board, depth - 1, alpha, beta, 1, maximizing_player);
        if (m < value)
          value = m;

        if (value <= alpha) {
          board_undo(board, col);
          break;
        };
        beta = beta < value ? beta : value;
        board_undo(board, col);
      }
    }
    return value;
  }
}

#define MAX_DEPTH 12

char bot_play_hard(Board *board) {
  if (cols_order[0] == 0) {
    generate_cols_order();
  }

  Board *thread_boards[COLS];

  int best_scores[COLS];
  int best_cols[COLS];

  for (int i = 0; i < COLS; i++) {
    board_copy(board, &thread_boards[i]);
    best_scores[i] = INT_MIN;
    best_cols[i] = -1;
  }

  const Player *bot_player = board_get_current_player(board);

#pragma omp parallel for
  for (int index = 0; index < COLS; index++) {
    int col = cols_order[index];

    if (board_is_move_valid(thread_boards[index], col)) {
      board_play(thread_boards[index], col);
      int score = hard_minimax(thread_boards[index], MAX_DEPTH, INT_MIN,
                               INT_MAX, 0, bot_player);
      board_undo(thread_boards[index], col);

      if (score > best_scores[index] ||
          (score == best_scores[index] &&
           (best_cols[index] == -1 ||
            abs((COLS / 2) - col) < abs((COLS / 2) - best_cols[index])))) {
        best_scores[index] = score;
        best_cols[index] = col;
      }
    }
  }

  for (int i = 0; i < COLS; i++) {
    board_free(thread_boards[i]);
  }

  int best_score = INT_MIN;
  int best_col = -1;

  for (int i = 0; i < COLS; i++) {
    if (best_scores[i] > best_score) {
      best_score = best_scores[i];
      best_col = best_cols[i];
    }
  }

  return best_col;
}

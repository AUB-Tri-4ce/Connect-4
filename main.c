#include "board.h"
#include "player.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char A_name[64];
  char B_name[64];

  printf("Player 1, input your name: ");
  scanf("%63s", A_name);
  printf("Player 2, input your name: ");
  scanf("%63s", B_name);

  char is_same_initial = A_name[0] == B_name[0];

  Player *A =
      player_new(A_name, is_same_initial ? toupper(A_name[0]) : A_name[0]);
  Player *B =
      player_new(B_name, is_same_initial ? tolower(B_name[0]) : B_name[0]);
  Player *players[2] = {A, B};

  Board *board = board_new(players);
  // check if board is null

  board_print(board);

  BoardState state;

  do {
    char column;
    do {
      printf("Player %s enter your move: \n",
             board_get_current_player(board)->name);
      scanf("%c", &column);

    } while (
        !board_is_move_valid(board, column)); // 0 means the move was invalid
    state = board_play(board, column);
    board_print(board);
  } while (state == BOARD_STATE_ONGOING);

  if (state == BOARD_STATE_TIE) {
    // print tie
  } else if (state == BOARD_STATE_WIN) {
    const Player *winner = board_get_winner(board);
    // print winner
  }

  board_free(board);
  player_free(A);
  player_free(B);
}

#include "board.h"
#include "player.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  setvbuf(stdout, NULL, _IONBF, 0);
  printf("\033[H\033[J");

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
  if (board == NULL) {
    printf("Unable to allocate board.");
    return EXIT_FAILURE;
  }

  board_print(board);

  BoardState state;

  do {
    int col;

    while (1) {
      printf("%s, enter a column (0-6): ",
             board_get_current_player(board)->name);

      int n = scanf("%d", &col);

      int c;
      while ((c = getchar()) != '\n' && c != EOF) {
      }

      if (n != 1) {
        printf("Invalid input. Please enter a number.\n");
        continue;
      }

      if (!board_is_move_valid(board, col)) {
        printf("Invalid move. Please try again.\n");
        continue;
      }
      break;
    }

    state = board_play(board, col);
    printf("\n");
    board_print(board);
  } while (state == BOARD_STATE_ONGOING);

  printf("\n");
  if (state == BOARD_STATE_TIE) {
    printf("It's a tie.\n");
  } else if (state == BOARD_STATE_WIN) {
    const Player *winner = board_get_winner(board);
    printf("The winner is %s!\n", winner->name);
  }

  board_free(board);
  player_free(A);
  player_free(B);
}

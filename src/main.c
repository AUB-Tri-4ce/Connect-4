#include "board.h"
#include "bot.h"
#include "player.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void resolve_initial_collisions(Player *A, Player *B) {
  char is_same_initial = A->initial == B->initial;

  if (is_same_initial) {
    A->initial = toupper(A->initial);
    B->initial = tolower(B->initial);
  }
}

static void read_human_input(Board *board, int *col) {
  const Player *player = board_get_current_player(board);

  while (1) {
    printf("%s (%c), enter a column (0-6): ", player->name, player->initial);

    int n = scanf("%d", col);

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }

    if (n != 1) {
      printf("Invalid input. Please enter a number.\n");
      continue;
    }

    if (!board_is_move_valid(board, *col)) {
      printf("Invalid move. Please try again.\n");
      continue;
    }
    break;
  }
}

static Player *create_player(int index) {
  printf("\e[0;32m[1]\e[0m Human\n");
  printf("\e[0;32m[2]\e[0m Bot - Easy\n");
  printf("\e[0;32m[3]\e[0m Bot - Moderate\n");
  printf("\e[0;32m[4]\e[0m Bot - Hard\n");
  printf("Choose Player %d type: ", index);

  char type;
  scanf(" %c", &type);

  Player *player;
  switch (type) {
  case '2':
    player = player_new("Easy Bot", 'E', PLAYER_BOT_EASY);
    break;
  case '3':
    player = player_new("Moderate Bot", 'M', PLAYER_BOT_MODERATE);
    break;
  case '4':
    player = player_new("Hard Bot", 'H', PLAYER_BOT_HARD);
    break;
  case '1':
  default:
    printf("Player %d, input your name: ", index);
    char name[64];
    scanf("%63s", name);
    player = player_new(name, name[0], PLAYER_HUMAN);
    break;
  }

  return player;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  setvbuf(stdout, NULL, _IONBF, 0);
  printf("\033[H\033[J");

  Player *A = create_player(1);
  printf("\n");
  Player *B = create_player(2);
  printf("\n");

  resolve_initial_collisions(A, B);

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

    const Player *current_player = board_get_current_player(board);

    switch (current_player->type) {
    case PLAYER_HUMAN:
      read_human_input(board, &col);
      break;

    case PLAYER_BOT_EASY:
      col = bot_play_easy(board);
      break;

    case PLAYER_BOT_MODERATE:
      col = bot_play_moderate(board);
      break;

    case PLAYER_BOT_HARD:
      col = bot_play_hard(board);
      break;
    }

    state = board_play(board, col);

    board_print(board);
    printf("\n");
  } while (state == BOARD_STATE_ONGOING);

  if (state == BOARD_STATE_TIE) {
    printf("It's a tie.\n");
  } else if (state == BOARD_STATE_WIN) {
    const Player *winner = board_get_winner(board);
    printf("The winner is %s (%c)!\n", winner->name, winner->initial);
  }

  board_free(board);
  player_free(A);
  player_free(B);

  printf("Press any key to exit...\n");
  getchar();
}

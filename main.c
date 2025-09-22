#include "board.h"
#include "player.h"

int main(int argc, char *argv[])
{
  Player *A = player_new("Name 1");
  Player *B = player_new("Name 2");

  Player players[2] = {A, B};

  Board *board = board_new(players);

  board_print(board);

  while (board_state(board) == BOARD_STATE_ONGOING)
  {
    Player *current_player = board_get_current_player(board);

    char column;
    do
    {
      printf("Player xyz enter your move:\n");
      column = scanf(); // ...
    } while (board_play(board, column) == 0); // 0 means the move was invalid

    board_print(board);
  }

  BoardState state = board_state(board);
  if (state == BOARD_STATE_TIE)
  {
    // print tie
  }
  else if (state == BOARD_STATE_WIN)
  {
    Player *winner = board_get_winner(board);
    // print winner
  }
}

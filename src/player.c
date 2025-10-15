#include "player.h"
#include <stdlib.h>
#include <string.h>

Player *player_new(char name[], char initial, PlayerType type) {
  Player *player = malloc(sizeof(Player));

  player->name = malloc(strlen(name) + 1);
  strcpy(player->name, name);

  player->initial = initial;
  player->type = type;

  return player;
}

char player_is_bot(const Player *player) { return player->type != PLAYER_HUMAN; }

void player_free(Player *player) {
  free(player->name);
  free(player);
}
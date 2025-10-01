#include "player.h"
#include <ctype.h>
#include <stdlib.h>

Player *player_new(char name[], char initial) {
  Player *player = malloc(sizeof(Player));

  player->name = name;
  player->initial = initial;

  return player;
}

void player_free(Player *player) { free(player); }
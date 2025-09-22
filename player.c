#include "player.h"

Player *player_new(char name[])
{
  Player *player = malloc(sizeof(Player));

  player->name = name;
  player->initial = name[0];

  return player;
}

void player_free(Player *player)
{
  free(player);
}
#pragma once

typedef struct
{
  char *name;
  char initial;
} Player;

Player *player_new(char[]);

void player_free(Player *player);
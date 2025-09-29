#pragma once

typedef struct {
  char *name;
  char initial;
} Player;

Player *player_new(char name[], char initial);

void player_free(Player *player);
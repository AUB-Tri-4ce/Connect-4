#pragma once

typedef enum {
  PLAYER_HUMAN,
  PLAYER_BOT_EASY,
  PLAYER_BOT_MODERATE,
  PLAYER_BOT_HARD,
} PlayerType;

typedef struct {
  char *name;
  char initial;
  PlayerType type;
} Player;

Player *player_new(char name[], char initial, PlayerType type);

char player_is_bot(const Player *player);

void player_free(Player *player);
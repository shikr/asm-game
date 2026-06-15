#pragma once

#include "levels.h"

struct Player {
  int x;
  int y;
};

struct GameState {
  char (*map)[SECTION_SIZE];
  int coins_collected;
  int step_count;
  int level;
  int unlocked;
  struct Player player;
  int top_position;
  int bottom_position;
};

void step(struct GameState *gs, int *completed, int *finished);
void draw_map(struct GameState gs);

extern struct Player positions[LEVEL_COUNT];

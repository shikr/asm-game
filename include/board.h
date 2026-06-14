#pragma once

#define SECTION_SIZE 20
#define SECTION_COUNT 9
#define MAP_AREA (SECTION_SIZE * SECTION_COUNT)

struct Player {
  int x;
  int y;
};

struct GameState {
  char (*map)[SECTION_SIZE];
  int coins_collected;
  int step_count;
  int level;
  struct Player player;
};

void step(struct GameState *gs, int *finished);
void draw_map(struct GameState gs);

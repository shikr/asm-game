#define TB_IMPL
#include "termbox2.h"

#include "board.h"
#include "levels.h"
#include "score.h"
#include <stdio.h>

int main() {
  int coins_count = count_coins(LEVEL_1[0], MAP_AREA * SECTION_SIZE, '$');

  struct GameState game_state = {
      .map = LEVEL_1,
      .coins_collected = 0,
      .step_count = 0,
      .level = 1,
      .player = {.x = 5, .y = 4},
  };

  int finished = 0;

  tb_init();

  while (finished != 1) {
    step(&game_state, &finished);
    draw_map(game_state);
  }
  tb_shutdown();

  int score = get_score(game_state.coins_collected, game_state.step_count,
                        game_state.level - 1);
  printf("\n\nmt: %i\nmc: %i\npuntj: %i\n", coins_count,
         game_state.coins_collected, score);
}

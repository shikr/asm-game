#define TB_IMPL
#include "termbox2.h"

#include "board.h"
#include "levels.h"
#include "score.h"

int main() {
  int coins_count = 0;
  int coins_collected = 0;
  int step_count = 0;

  int finished = 0;

  tb_init();

  for (int i = 0; i < LEVEL_COUNT; i++) {
    struct GameState game_state = {
        .map = i == 0 ? LEVEL_1 : (i == 1 ? LEVEL_2 : LEVEL_3),
        .coins_collected = 0,
        .step_count = 0,
        .level = i + 1,
        .unlocked = 0,
        .player = positions[i],
        .top_position = 0,
        .bottom_position = SECTION_SIZE,
    };

    int completed = 0;

    while (!completed && !finished) {
      step(&game_state, &completed, &finished);
      draw_map(game_state);
    }

    coins_count += count_coins(game_state.map[0], MAP_AREA * SECTION_SIZE, '$');
    coins_collected += game_state.coins_collected;
    step_count += game_state.step_count;

    if (finished)
      break;

    // int score = get_score(game_state.coins_collected, game_state.step_count,
    //                       game_state.level - 1);
    // printf("\n\nmt: %i\nmc: %i\npuntj: %i\n", coins,
    // game_state.coins_collected,
    //        score);
  }

  tb_shutdown();

  if (finished) {
    printf("Juego terminado por el jugador. Gracias por jugar!\n");
  } else {
    printf("¡Felicidades! Has completado todos los niveles.\n");
    printf("Monedas totales: %d\n", coins_count);
    printf("Monedas recolectadas: %d\n", coins_collected);
    printf("Pasos totales: %d\n", step_count);
  }
}

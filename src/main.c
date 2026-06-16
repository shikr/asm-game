#define TB_IMPL
#include "termbox2.h"

#include "board.h"
#include "levels.h"
#include "score.h"
#include <stdio.h>

void wait_for_keypress() {
  struct tb_event ev;
  do {
    tb_poll_event(&ev);
  } while (ev.type != TB_EVENT_KEY);
}

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
      draw_map(game_state);
      step(&game_state, &completed, &finished);
    }

    int coins = count_coins(game_state.map[0], MAP_AREA * SECTION_SIZE, '$');
    coins_count += coins;
    coins_collected += game_state.coins_collected;
    step_count += game_state.step_count;

    tb_clear();

    if (finished)
      break;

    // mostrar resultados en el centro de la pantalla
    char msg[] = "Nivel completado! Presiona cualquier tecla para continuar...";
    int msg_len = sizeof(msg) - 1;

    int term_width = tb_width();
    int term_height = tb_height();
    int msg_x = (term_width - msg_len) / 2;
    int msg_y = (term_height - 3) / 2;

    tb_print(msg_x, msg_y, TB_WHITE, TB_DEFAULT, msg);
    tb_printf(msg_x, msg_y + 1, TB_WHITE, TB_DEFAULT,
              "Monedas recolectadas: %d / %d", game_state.coins_collected,
              coins);
    tb_printf(msg_x, msg_y + 2, TB_WHITE, TB_DEFAULT, "Pasos: %d",
              game_state.step_count);
    tb_present();
    wait_for_keypress();
  }

  if (finished) {
    tb_shutdown();

    printf("Juego terminado por el jugador. Gracias por jugar!\n");
  } else {
    tb_clear();

    char msg[] = "¡Felicidades! Has completado todos los niveles.";
    int msg_len = sizeof(msg) - 1;
    int score = get_score(coins_collected, step_count, LEVEL_COUNT);

    int term_width = tb_width();
    int term_height = tb_height();
    int msg_x = (term_width - msg_len) / 2;
    int msg_y = (term_height - 6) / 2;

    tb_print(msg_x, msg_y, TB_WHITE, TB_DEFAULT, msg);
    tb_printf(msg_x, msg_y + 1, TB_WHITE, TB_DEFAULT, "Monedas: %d / %d",
              coins_collected, coins_count);
    tb_printf(msg_x, msg_y + 2, TB_WHITE, TB_DEFAULT, "Pasos totales: %d",
              step_count);
    tb_printf(msg_x, msg_y + 3, TB_WHITE, TB_DEFAULT, "Niveles completados: %d",
              LEVEL_COUNT);
    tb_printf(msg_x, msg_y + 4, TB_WHITE, TB_DEFAULT, "Puntaje final: %d",
              score);
    tb_print(msg_x, msg_y + 5, TB_WHITE, TB_DEFAULT,
             "Presiona cualquier tecla para continuar...");
    tb_present();

    wait_for_keypress();

    tb_shutdown();
  }
}

#include "board.h"
#include "movement.h"
#include "termbox2.h"

int top_position = 0;
int bottom_position = SECTION_SIZE;

void step(struct GameState *gs, int *finished) {
  struct tb_event ev;
  int next_x_pos = gs->player.x;
  int next_y_pos = gs->player.y;

  while (1) {
    tb_poll_event(&ev);
    if (ev.type == TB_EVENT_KEY) {
      if (ev.ch) {
        switch (ev.ch) {
        case 'w':
          next_y_pos--;
          break;

        case 'a':
          next_x_pos--;
          break;

        case 's':
          next_y_pos++;
          break;

        case 'd':
          next_x_pos++;
          break;

        case 'q':
          *finished = 1;
          break;

        default:
          break;
        }
        break;
      }
    }
  }

  gs->step_count++;

  // si es una pared no hace nada
  if (validate_movement(gs->map[0], SECTION_SIZE, next_y_pos, next_x_pos)) {
    return;
  }

  // si no es pared, entonces checar que es
  if (detect_object(gs->map[0], SECTION_SIZE, next_y_pos, next_x_pos, '$')) {
    gs->coins_collected++;
    gs->map[next_y_pos][next_x_pos] = ' ';
    gs->player.x = next_x_pos;
    gs->player.y = next_y_pos;
  }

  if (detect_object(gs->map[0], SECTION_SIZE, next_y_pos, next_x_pos, ' ')) {
    gs->player.x = next_x_pos;
    gs->player.y = next_y_pos;
  }

  if (detect_object(gs->map[0], SECTION_SIZE, next_y_pos, next_x_pos, '>')) {
    // reajustar limites
    top_position += 20 * 3;
    bottom_position += 20 * 3;
    // poner al jugador en la posicion inicial de la zona
    gs->player.x = 1;
    gs->player.y += 20 * 3;
  }

  if (detect_object(gs->map[0], SECTION_SIZE, next_y_pos, next_x_pos, '<')) {
    // reajustar limites
    top_position -= 20 * 3;
    bottom_position -= 20 * 3;
    // poner al jugador en la posicion inicial de la zona
    gs->player.x = 18;
    gs->player.y -= 20 * 3;
  }

  if (detect_object(gs->map[0], SECTION_SIZE, next_y_pos, next_x_pos, '0')) {
    // reajustar limites
    top_position -= 20;
    bottom_position -= 20;
    // poner al jugador en la posicion inicial de la zona
    gs->player.y -= 3;
  }

  if (detect_object(gs->map[0], SECTION_SIZE, next_y_pos, next_x_pos, 'O')) {
    // reajustar limites
    top_position += 20;
    bottom_position += 20;
    // poner al jugador en la posicion inicial de la zona
    gs->player.y += 3;
  }

  if (detect_object(gs->map[0], SECTION_SIZE, next_y_pos, next_x_pos, 'K')) {
    gs->unlocked = 1;
    gs->player.x = next_x_pos;
    gs->player.y = next_y_pos;
  }

  if (detect_object(gs->map[0], SECTION_SIZE, next_y_pos, next_x_pos, 'E')) {
    if (gs->unlocked) {
      *finished = 1;
    }
  }
}

void draw_map(struct GameState gs) {
  tb_clear();

  // sacar tamaño de al terminal
  int ancho_terminal = tb_width();
  int alto_terminal = tb_height();
  // sacar medidas del mapa
  int ancho_mapa =
      SECTION_SIZE * 2; //*2 para que se centre bien pq al mostrar el mapa se
                        // le suma al offset x*2 para que no se vea todo junto
  int alto_mapa = bottom_position - top_position;
  // sacar el offset
  int offsetX = (ancho_terminal - ancho_mapa) / 2;
  int offsetY = (alto_terminal - alto_mapa) / 2;
  // que el offset minimo sea 0,0 por si se achica la terminal
  if (offsetX < 0) {
    offsetX = 0;
  }
  if (offsetY < 0) {
    offsetY = 0;
  }

  // imprimir HUD
  tb_printf(2, 0, TB_WHITE, TB_DEFAULT, "monedas: %d", gs.coins_collected);
  tb_printf(40, 0, TB_YELLOW, TB_DEFAULT, "Mapa: %d", 1);

  // recorrer e imprimir una seccion de 20x20 del mapa
  int x = 0;
  int y = 0;

  for (int i = top_position; i < bottom_position; i++) {
    for (int j = 0; j < SECTION_SIZE; j++) {
      int px = offsetX + x * 2;
      int py = offsetY + y;

      if (i == gs.player.y && j == gs.player.x) {
        tb_set_cell(px, py, 'P', TB_WHITE, TB_DEFAULT);
      } else if (gs.map[i][j] == 'K') {
        tb_set_cell(px, py, 'K', gs.unlocked ? TB_YELLOW : TB_RED, TB_DEFAULT);
      } else {
        tb_set_cell(px, py, gs.map[i][j], TB_GREEN, TB_DEFAULT);
      }
      x++;
    }
    x = 0;
    y++;
  }
  tb_present();
}

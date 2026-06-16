#pragma once

int count_coins(char *map, int cell_count, char coin_symbol);

int get_score(int coins_collected, int steps_taken, int levels_completed);

int count_empty(char *map, int total_columns);

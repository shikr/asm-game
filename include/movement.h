#pragma once

#include <stdbool.h>

bool validate_movement(char *map, int total_columns, int new_row,
                       int new_column);

bool detect_object(char *map, int total_columns, int new_row, int new_column,
                   char object);

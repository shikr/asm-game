#pragma once

#define SECTION_SIZE 20
#define SECTION_COUNT 9
#define MAP_AREA (SECTION_SIZE * SECTION_COUNT)

#define LEVEL_COUNT 3

extern char LEVEL_1[MAP_AREA][SECTION_SIZE] __attribute__((nonstring));

extern char LEVEL_2[MAP_AREA][SECTION_SIZE] __attribute__((nonstring));

extern char LEVEL_3[MAP_AREA][SECTION_SIZE] __attribute__((nonstring));

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

typedef struct {
    int x, y;
} Point;

void init_game();
void update();
void draw();
void handle_input();
bool is_game_over();

#endif

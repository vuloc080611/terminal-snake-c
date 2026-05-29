#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

#define MAX_SNAKE_LEN 100

typedef struct {
    int x[MAX_SNAKE_LEN];
    int y[MAX_SNAKE_LEN];
    int length;
} Snake;

void init_snake(Snake *snake, int start_x, int start_y);
void move_snake(Snake *snake, int dx, int dy);
void grow_snake(Snake *snake, int dx, int dy);
bool check_self_collision(Snake *snake);
void draw_snake(Snake *snake, int height, int width);

#endif

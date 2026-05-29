#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

typedef struct SnakeSegment {
    int x, y;
    struct SnakeSegment *next;
} SnakeSegment;

typedef struct {
    SnakeSegment *head;
    SnakeSegment *tail;
    int length;
} Snake;

Snake* create_snake(int start_x, int start_y);
void free_snake(Snake *snake);
void move_snake(Snake *snake, int dx, int dy);
bool grow_snake(Snake *snake, int dx, int dy);
bool check_self_collision(Snake *snake);
void draw_snake(Snake *snake);

#endif

#include "snake.h"
#include <ncurses.h>

void init_snake(Snake *snake, int start_x, int start_y) {
    snake->length = 3;
    for (int i = 0; i < snake->length; i++) {
        snake->x[i] = start_x - i;
        snake->y[i] = start_y;
    }
}

void move_snake(Snake *snake, int dx, int dy) {
    // Dịch chuyển các segment từ đuôi lên đầu
    for (int i = snake->length - 1; i > 0; i--) {
        snake->x[i] = snake->x[i-1];
        snake->y[i] = snake->y[i-1];
    }
    snake->x[0] += dx;
    snake->y[0] += dy;
}

void grow_snake(Snake *snake, int dx, int dy) {
    if (snake->length >= MAX_SNAKE_LEN) return;
    // Thêm một segment ở vị trí đuôi hiện tại (sẽ được move lần sau)
    snake->x[snake->length] = snake->x[snake->length-1];
    snake->y[snake->length] = snake->y[snake->length-1];
    snake->length++;
}

bool check_self_collision(Snake *snake) {
    for (int i = 1; i < snake->length; i++) {
        if (snake->x[0] == snake->x[i] && snake->y[0] == snake->y[i])
            return true;
    }
    return false;
}

void draw_snake(Snake *snake, int height, int width) {
    for (int i = 0; i < snake->length; i++) {
        if (snake->x[i] >= 0 && snake->x[i] < width && snake->y[i] >= 0 && snake->y[i] < height)
            mvprintw(snake->y[i], snake->x[i], "O");
    }
}

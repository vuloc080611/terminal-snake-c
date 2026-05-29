#include "game.h"
#include "snake.h"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

static Snake snake;
static Point food;
static int score;
static int direction_dx, direction_dy; // 1, -1, 0
static int next_dx, next_dy;
static int height, width;
static bool game_over;

void init_game() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    getmaxyx(stdscr, height, width);
    
    srand(time(NULL));
    
    init_snake(&snake, width/2, height/2);
    direction_dx = 1; direction_dy = 0;
    next_dx = 1; next_dy = 0;
    score = 0;
    game_over = false;
    
    // Tạo food đầu tiên
    do {
        food.x = rand() % (width - 2) + 1;
        food.y = rand() % (height - 2) + 1;
    } while (abs(food.x - snake.x[0]) < 3 && abs(food.y - snake.y[0]) < 3);
}

void handle_input() {
    int ch = getch();
    switch(ch) {
        case KEY_UP:    if (direction_dy != 1)  { next_dx = 0; next_dy = -1; } break;
        case KEY_DOWN:  if (direction_dy != -1) { next_dx = 0; next_dy = 1; } break;
        case KEY_LEFT:  if (direction_dx != 1)  { next_dx = -1; next_dy = 0; } break;
        case KEY_RIGHT: if (direction_dx != -1) { next_dx = 1; next_dy = 0; } break;
        case 'q': game_over = true; break;
    }
    direction_dx = next_dx;
    direction_dy = next_dy;
}

void update() {
    move_snake(&snake, direction_dx, direction_dy);
    
    // Kiểm tra va chạm với tường
    if (snake.x[0] <= 0 || snake.x[0] >= width-1 || snake.y[0] <= 0 || snake.y[0] >= height-1)
        game_over = true;
    
    // Kiểm tra tự cắn
    if (check_self_collision(&snake))
        game_over = true;
    
    // Kiểm tra ăn food
    if (snake.x[0] == food.x && snake.y[0] == food.y) {
        grow_snake(&snake, 0, 0); // Thêm segment
        score++;
        // Tạo food mới
        do {
            food.x = rand() % (width - 2) + 1;
            food.y = rand() % (height - 2) + 1;
        } while (0); // Có thể kiểm tra trùng với thân rắn, bỏ qua để đơn giản
    }
}

void draw() {
    clear();
    // Vẽ khung
    for (int i = 0; i < width; i++) {
        mvaddch(0, i, '#');
        mvaddch(height-1, i, '#');
    }
    for (int i = 0; i < height; i++) {
        mvaddch(i, 0, '#');
        mvaddch(i, width-1, '#');
    }
    // Vẽ food
    mvaddch(food.y, food.x, '@');
    // Vẽ rắn
    draw_snake(&snake, height, width);
    // Hiển thị điểm
    mvprintw(0, 2, "Score: %d", score);
    if (game_over) {
        mvprintw(height/2, width/2 - 8, "GAME OVER! Press 'r' to restart");
        refresh();
        int ch = getch();
        if (ch == 'r') {
            init_game();
            game_over = false;
        }
    }
    refresh();
}

bool is_game_over() {
    return game_over;
}

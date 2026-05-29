#include "game.h"
#include <unistd.h>

int main() {
    init_game();
    while (!is_game_over()) {
        handle_input();
        update();
        draw();
      
        usleep(100000); // 0.1 giây
    }
    endwin();
    return 0;
}

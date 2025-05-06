#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "display.h"
#include "game.h"

int main() {
    int board_size = 4;
    t_game game;
    t_options options;
    options.grid_size = 4;

    srand(time(NULL));

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();
        init_display_colors();
    }

    while (1) {
        int menu_choice = show_menu();

        if (menu_choice == 2)
            break;
        else if (menu_choice == 1)
        { 
            draw_options_menu(&options);
            board_size = options.grid_size;
        }
        else if (menu_choice == 0)
        {
            initialize_game(&game, board_size);
            add_random_tile(&game, board_size);
            add_random_tile(&game, board_size);

            draw_board(&game, options.grid_size);

            if (print(&game, options.grid_size) == -1)
                goto cleanup;
            
            if (draw_end_game_menu() == -1)
				goto cleanup;
        }
    }

cleanup:
    endwin();
}

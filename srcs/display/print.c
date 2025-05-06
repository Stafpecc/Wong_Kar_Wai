#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "display.h"
#include "game.h"

#define MIN_WIDTH 40
#define MIN_HEIGHT 20

static int check_window_size(int *height, int *width)
{
    getmaxyx(stdscr, *height, *width);
    if (*height < MIN_HEIGHT || *width < MIN_WIDTH) {
        clear();
        mvprintw(0, 0, "[Error] Window too small (%d x %d).", *width, *height);
        mvprintw(2, 0, "Please resize the window...");
        mvprintw(4, 0, "Press ENTER to continue, or ESC to quit.");
        refresh();
        
        int ch;
        while (1) {
            ch = getch();
            getmaxyx(stdscr, *height, *width);

            if (is_term_resized(*height, *width)) {
                endwin();
                refresh();
                clear();
                getmaxyx(stdscr, *height, *width);
            }

            if (*height < MIN_HEIGHT || *width < MIN_WIDTH) {
                clear();
                mvprintw(0, 0, "[Error] Window too small (%d x %d).", *width, *height);
                mvprintw(2, 0, "Please resize the window...");
                mvprintw(4, 0, "Press ENTER to continue, or ESC to quit.");
                refresh();
            }

            if (ch == KEY_ESC) {
                return -1;
            }

            if (*height >= MIN_HEIGHT && *width >= MIN_WIDTH) {
                clear();
                mvprintw(0, 0, "Size OK (%d x %d).", *width, *height);
                mvprintw(2, 0, "Press ENTER to continue, or ESC to quit.");
                refresh();

                if (ch == '\n' || ch == KEY_ENTER)
                    break;
            }
        }
        return 0;
    }
    return 1;
}

static int handle_player_input(int ch, t_game *game, int grid_size)
{
    int moved = 0;
    switch (ch) {
        case KEY_UP:
            moved = move_up(game, grid_size);
            break;
        case KEY_DOWN:
            moved = move_down(game, grid_size);
            break;
        case KEY_LEFT:
            moved = move_left(game, grid_size);
            break;
        case KEY_RIGHT:
            moved = move_right(game, grid_size);
            break;
        case 'r':
        case 'R':
            initialize_game(game, grid_size);
            add_random_tile(game, grid_size);
            add_random_tile(game, grid_size);
            moved = 1;
            break;
        case KEY_ESC:
            return -1;
    }
    return moved;
}

static void handle_game_over(t_game *game, int grid_size)
{
    save_high_score(game);
    draw_game_over();
    if (getch() == 'r' || getch() == 'R') {
        initialize_game(game, grid_size);
        add_random_tile(game, grid_size);
        add_random_tile(game, grid_size);
    }
}

static void handle_game_win(t_game *game)
{
    save_high_score(game);
    draw_win_message();
}

int print(t_game *game, int grid_size)
{
    int ch;
    int height, width;

    getmaxyx(stdscr, height, width);

    while ((ch = getch())) {
        if (is_term_resized(height, width)) {
            endwin();
            refresh();
            clear();
            getmaxyx(stdscr, height, width);
        }

        if (check_window_size(&height, &width) == -1) {
            return -1;
        }

        clear();
        int moved = handle_player_input(ch, game, grid_size);
        if (moved == -1)
			return -1;
		
        if (moved) {
            add_random_tile(game, grid_size);
        }

        draw_board(game, grid_size);

        if (game_over(game, grid_size)) {
            handle_game_over(game, grid_size);
        }

        if (game_won(game, grid_size)) {
            handle_game_win(game);
        }

        refresh();
    }
    return 0;
}

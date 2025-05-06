#include <ncurses.h>
#include <string.h>

#include "display.h"
#include "libft.h"

void init_display_colors()
{
	init_pair(COLOR_PAIR_BG, COLOR_BLACK, COLOR_WHITE);
	init_pair(COLOR_PAIR_2, COLOR_BLACK, COLOR_WHITE);
	init_pair(COLOR_PAIR_4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_PAIR_8, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(COLOR_PAIR_16, COLOR_WHITE, COLOR_RED);
	init_pair(COLOR_PAIR_32, COLOR_WHITE, COLOR_GREEN);
	init_pair(COLOR_PAIR_64, COLOR_WHITE, COLOR_CYAN);
	init_pair(COLOR_PAIR_128, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_PAIR_256, COLOR_BLACK, COLOR_CYAN);
	init_pair(COLOR_PAIR_512, COLOR_WHITE, COLOR_BLUE);
	init_pair(COLOR_PAIR_1024, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(COLOR_PAIR_2048, COLOR_WHITE, COLOR_RED);
	init_pair(COLOR_PAIR_HIGHER, COLOR_WHITE, COLOR_BLACK);
}

int get_tile_color(int value)
{
	switch (value) {
		case 0: return COLOR_PAIR_BG;
		case 2: return COLOR_PAIR_2;
		case 4: return COLOR_PAIR_4;
		case 8: return COLOR_PAIR_8;
		case 16: return COLOR_PAIR_16;
		case 32: return COLOR_PAIR_32;
		case 64: return COLOR_PAIR_64;
		case 128: return COLOR_PAIR_128;
		case 256: return COLOR_PAIR_256;
		case 512: return COLOR_PAIR_512;
		case 1024: return COLOR_PAIR_1024;
		case 2048: return COLOR_PAIR_2048;
		default: return COLOR_PAIR_HIGHER;
	}
}

void draw_tile(int y, int x, int value)
{
    int tile_width = 6;
    int tile_height = 2;

    int color = get_tile_color(value);
    attron(COLOR_PAIR(color));

    for (int i = 0; i <= tile_height; i++)
        mvhline(y + i, x, ' ', tile_width);
    
    if (value != 0)
    {
        char number[20];
        int len = 0;

        if (value == 0)
            number[len++] = '0';
        else
		{
            int temp_value = value;
            while (temp_value > 0)
		{
                number[len++] = (temp_value % 10) + '0'; 
                temp_value /= 10;
            }
            for (int i = 0; i < len / 2; i++)
			{
                char temp = number[i];
                number[i] = number[len - 1 - i];
                number[len - 1 - i] = temp;
            }
        }
        if (len > tile_width)
            len = tile_width;

        int offset_x = (tile_width - len) / 2;
        int offset_y = tile_height / 2;

        mvprintw(y + offset_y, x + offset_x, "%.*s", len, number);
    }

    attroff(COLOR_PAIR(color));
}

void draw_board(t_game *game, int grid_size)
{
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    int tile_width = 6;
    int tile_height = 2;

    int board_width = grid_size * (tile_width + 1) + 1;
    int board_height = grid_size * (tile_height + 1) + 1;

    int start_y = (term_height - board_height) / 2;
    int start_x = (term_width - board_width) / 2;

    clear();

    mvprintw(start_y - 3, start_x, "2048");
    load_high_score(game);
    mvprintw(0, 0, "High Score : %lu", game->high_score);
    mvprintw(start_y - 2, start_x, "Score: %lu", game->score);

    for (int i = 0; i <= grid_size; i++) {
        mvprintw(start_y + i * (tile_height + 1), start_x, "+");
        for (int j = 0; j < grid_size; j++) {
            for (int k = 0; k < tile_width; k++) {
                printw("-");
            }
            printw("+");
        }
    }

    for (int i = 0; i < grid_size; i++) {
        for (int k = 1; k <= tile_height; k++) {
            mvprintw(start_y + i * (tile_height + 1) + k, start_x, "|");
            for (int j = 0; j < grid_size; j++) {
                for (int m = 0; m < tile_width; m++) {
                    printw(" ");
                }
                printw("|");
            }
        }
    }

    for (int row = 0; row < grid_size; row++) {
        for (int col = 0; col < grid_size; col++) {
            int tile_y = start_y + row * (tile_height + 1) + 1;
            int tile_x = start_x + col * (tile_width + 1) + 1;
            draw_tile(tile_y, tile_x, game->board[row][col]);
        }
    }

    mvprintw(term_height - 4, 0, "Arrow keys: Move");
    mvprintw(term_height - 3, 0, "R: Restart");
    mvprintw(term_height - 2, 0, "ESC: Quit");

    refresh();
}


void draw_score(int score)
{
	mvprintw(2, 0, "Score: %d", score);
}

void draw_game_over(void)
{
	clear();
	draw_end_game_menu();
}

void draw_win_message()
{
	attron(COLOR_PAIR(COLOR_PAIR_2048) | A_BOLD);
	mvprintw(10, 30, "You won! Continue playing?");
	attroff(COLOR_PAIR(COLOR_PAIR_2048) | A_BOLD);
}

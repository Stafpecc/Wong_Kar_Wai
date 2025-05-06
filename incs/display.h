#ifndef DISPLAY_H
# define DISPLAY_H

# include "game.h"

# define KEY_ESC 27
# define KEY_ENTR 10
# define KEY_R_LOW 114
# define KEY_R_UP 82

# define COLOR_PAIR_BG 1
# define COLOR_PAIR_2 2
# define COLOR_PAIR_4 3
# define COLOR_PAIR_8 4
# define COLOR_PAIR_16 5
# define COLOR_PAIR_32 6
# define COLOR_PAIR_64 7
# define COLOR_PAIR_128 8
# define COLOR_PAIR_256 9
# define COLOR_PAIR_512 10
# define COLOR_PAIR_1024 11
# define COLOR_PAIR_2048 12
# define COLOR_PAIR_HIGHER 13

# define DELAY 90000
# define TITLE_LINES 1
# define SUBTITLE_LINES 1
# define MENU_LINES 3

void	init_display_colors();

void	draw_board(t_game *game, int grid_size);
void	draw_score(int score);
void	draw_game_over();
void	draw_win_message();

int		show_menu();
void	draw_options_menu(t_options *options);
int		draw_end_game_menu();

int print(t_game *game, int grid_size);

#endif

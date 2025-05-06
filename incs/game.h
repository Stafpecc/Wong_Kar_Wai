#ifndef GAME_H
# define GAME_H

enum    e_const
{
	WIN_VALUE = 2048
};

typedef struct s_game
{
	int board[5][5];
	unsigned long int score;
	int moves;
	int game_won;
	unsigned long int high_score; 
}   t_game;

typedef struct s_options
{
    int grid_size;
} t_options;

void	initialize_game(t_game *game, int board_size);
void	add_random_tile(t_game *game, int board_size);

int		game_over(t_game *game, int board_size);
int		game_won(t_game *game, int board_size);
int		has_empty_tiles(t_game *game, int board_size);

int		move_left(t_game *game, int board_size);
int		move_right(t_game *game, int board_size);
int		move_up(t_game *game, int board_size);
int		move_down(t_game *game, int board_size);


void load_high_score(t_game *game);
void save_high_score(t_game *game);

#endif

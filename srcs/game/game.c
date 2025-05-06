#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "libft.h"

void initialize_game(t_game *game, int board_size)
{
    for (int i = 0; i < board_size; i++)
        for (int j = 0; j < board_size; j++)
            game->board[i][j] = 0;
    
    game->score = 0;
    game->moves = 0;
    game->game_won = 0;
}

int has_empty_tiles(t_game *game, int board_size)
{
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (game->board[i][j] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void add_random_tile(t_game *game, int board_size)
{
    if (!has_empty_tiles(game, board_size)) {
        return;
    }

    int row, col;
    do {
        row = rand() % board_size;
        col = rand() % board_size;
    } while (game->board[row][col] != 0);

    game->board[row][col] = (rand() % 10 == 0) ? 4 : 2;
}

int can_move(t_game *game, int board_size)
{
    if (has_empty_tiles(game, board_size)) {
        return 1;
    }
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size - 1; j++) {
            if (game->board[i][j] == game->board[i][j + 1]) {
                return 1;
            }
        }
    }
    for (int j = 0; j < board_size; j++) {
        for (int i = 0; i < board_size - 1; i++) {
            if (game->board[i][j] == game->board[i + 1][j]) {
                return 1;
            }
        }
    }
    return 0;
}

int game_over(t_game *game, int board_size)
{
    return !can_move(game, board_size);
}

int game_won(t_game *game, int board_size)
{
    if (game->game_won) {
        return 1;
    }
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (game->board[i][j] >= WIN_VALUE) {
                game->game_won = 1;
                return 1;
            }
        }
    }
    return 0;
}

int move_left(t_game *game, int board_size)
{
    int moved = 0;

    for (int row = 0; row < board_size; row++) {
        for (int col = 0; col < board_size; col++) {
            if (game->board[row][col] == 0) {
                for (int next_col = col + 1; next_col < board_size; next_col++) {
                    if (game->board[row][next_col] != 0) {
                        game->board[row][col] = game->board[row][next_col];
                        game->board[row][next_col] = 0;
                        moved = 1;
                        break;
                    }
                }
            }
        }
        for (int col = 0; col < board_size - 1; col++) {
            if (game->board[row][col] != 0 && game->board[row][col] == game->board[row][col + 1]) {
                game->board[row][col] *= 2;
                game->board[row][col + 1] = 0;
                game->score += game->board[row][col];
                moved = 1;
            }
        }
        for (int col = 0; col < board_size; col++) {
            if (game->board[row][col] == 0) {
                for (int next_col = col + 1; next_col < board_size; next_col++) {
                    if (game->board[row][next_col] != 0) {
                        game->board[row][col] = game->board[row][next_col];
                        game->board[row][next_col] = 0;
                        moved = 1;
                        break;
                    }
                }
            }
        }
    }

    if (moved) {
        game->moves++;
    }

    return moved;
}

int move_right(t_game *game, int board_size)
{
    int moved = 0;

    for (int row = 0; row < board_size; row++) {
        for (int col = board_size - 1; col >= 0; col--) {
            if (game->board[row][col] == 0) {
                for (int next_col = col - 1; next_col >= 0; next_col--) {
                    if (game->board[row][next_col] != 0) {
                        game->board[row][col] = game->board[row][next_col];
                        game->board[row][next_col] = 0;
                        moved = 1;
                        break;
                    }
                }
            }
        }

        for (int col = board_size - 1; col > 0; col--) {
            if (game->board[row][col] != 0 && game->board[row][col] == game->board[row][col - 1]) {
                game->board[row][col] *= 2;
                game->board[row][col - 1] = 0;
                game->score += game->board[row][col];
                moved = 1;
            }
        }

        for (int col = board_size - 1; col >= 0; col--) {
            if (game->board[row][col] == 0) {
                for (int next_col = col - 1; next_col >= 0; next_col--) {
                    if (game->board[row][next_col] != 0) {
                        game->board[row][col] = game->board[row][next_col];
                        game->board[row][next_col] = 0;
                        moved = 1;
                        break;
                    }
                }
            }
        }
    }

    if (moved) {
        game->moves++;
    }

    return moved;
}

int move_up(t_game *game, int board_size)
{
    int moved = 0;

    for (int col = 0; col < board_size; col++) {
        for (int row = 0; row < board_size; row++) {
            if (game->board[row][col] == 0) {
                for (int next_row = row + 1; next_row < board_size; next_row++) {
                    if (game->board[next_row][col] != 0) {
                        game->board[row][col] = game->board[next_row][col];
                        game->board[next_row][col] = 0;
                        moved = 1;
                        break;
                    }
                }
            }
        }

        for (int row = 0; row < board_size - 1; row++) {
            if (game->board[row][col] != 0 && game->board[row][col] == game->board[row + 1][col]) {
                game->board[row][col] *= 2;
                game->board[row + 1][col] = 0;
                game->score += game->board[row][col];
                moved = 1;
            }
        }

        for (int row = 0; row < board_size; row++) {
            if (game->board[row][col] == 0) {
                for (int next_row = row + 1; next_row < board_size; next_row++) {
                    if (game->board[next_row][col] != 0) {
                        game->board[row][col] = game->board[next_row][col];
                        game->board[next_row][col] = 0;
                        moved = 1;
                        break;
                    }
                }
            }
        }
    }

    if (moved) {
        game->moves++;
    }

    return moved;
}

int move_down(t_game *game, int board_size)
{
    int moved = 0;

    for (int col = 0; col < board_size; col++) {
        for (int row = board_size - 1; row >= 0; row--) {
            if (game->board[row][col] == 0) {
                for (int next_row = row - 1; next_row >= 0; next_row--) {
                    if (game->board[next_row][col] != 0) {
                        game->board[row][col] = game->board[next_row][col];
                        game->board[next_row][col] = 0;
                        moved = 1;
                        break;
                    }
                }
            }
        }

        for (int row = board_size - 1; row > 0; row--) {
            if (game->board[row][col] != 0 && game->board[row][col] == game->board[row - 1][col]) {
                game->board[row][col] *= 2;
                game->board[row - 1][col] = 0;
                game->score += game->board[row][col];
                moved = 1;
            }
        }

        for (int row = board_size - 1; row >= 0; row--) {
            if (game->board[row][col] == 0) {
                for (int next_row = row - 1; next_row >= 0; next_row--) {
                    if (game->board[next_row][col] != 0) {
                        game->board[row][col] = game->board[next_row][col];
                        game->board[next_row][col] = 0;
                        moved = 1;
                        break;
                    }
                }
            }
        }
    }

    if (moved) {
        game->moves++;
    }

    return moved;
}

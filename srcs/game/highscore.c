#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "game.h"

void load_high_score(t_game *game)
{
    int fd = open("highscore.txt", O_RDONLY);
    if (fd == -1)
    {
        game->high_score = 0;
        return;
    }

    char buffer[20];
    int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        game->high_score = ft_atoi(buffer);
    }
    else
    {
        game->high_score = 0;
    }

    close(fd);
}

static int ft_itos(int n, char *str)
{
    int i = 0;
    int tmp = n;
    char rev[20];

    if (n == 0)
    {
        str[0] = '0';
        str[1] = '\n';
        return 2;
    }

    while (tmp > 0)
    {
        rev[i++] = (tmp % 10) + '0';
        tmp /= 10;
    }

    int j = 0;
    while (i > 0)
    {
        str[j++] = rev[--i];
    }
    str[j++] = '\n';
    return j;
}

void save_high_score(t_game *game)
{
    if (game->score > game->high_score)
    {
        int fd = open("highscore.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            return;

        char buffer[20];
        int len = ft_itos(game->score, buffer);
        write(fd, buffer, len);
        close(fd);
    }
}
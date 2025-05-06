#include <ncurses.h>
#include <string.h>

#include "display.h"
#include "libft.h"

int draw_end_game_menu(void)
{
    int highlight = 0;
    int choice;
    int options_count = 1;
    char *choices[] = {"Please enter escape to quit"};

    while (1) {
        int term_height, term_width;
        getmaxyx(stdscr, term_height, term_width);

        clear();
        mvprintw(term_height / 2 - 3, (term_width - 25) / 2, "Congratulations, You Lose");
        mvprintw(term_height / 2 - 2, (term_width - 20) / 2, "Choose an option:");

        for (int i = 0; i < options_count; i++) {
            if (i == highlight)
                attron(A_REVERSE);
            mvprintw(term_height / 2 + i, (term_width - ft_strlen(choices[i])) / 2, "%s", choices[i]);
            attroff(A_REVERSE);
        }

        choice = getch();

        switch (choice)
        {
            case KEY_ESC:
                if (highlight == 0) {
                    return -1;
                }
                break;
        }
        refresh();
    }
    return 0;
}

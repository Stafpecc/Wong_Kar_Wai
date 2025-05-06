#include <ncurses.h>

typedef struct s_options {
    int grid_size;
} t_options;

void draw_options_menu(t_options *options)
{
    int highlight = 0;
    int choice;
    int options_count = 3;
    char *choices[] = {"4x4 Grid", "5x5 Grid", "Main Menu"};

    while (1) {
        clear();
        mvprintw(2, (COLS - 10) / 2, "OPTIONS");
        mvprintw(3, (COLS - 20) / 2, "--------------------");

        for (int i = 0; i < options_count; i++) {
            int y_offset = 5 + i;
            if (i == 2)
                y_offset++;

            if (i == highlight)
                attron(A_REVERSE);

            if (i == 0)
                mvprintw(y_offset, (COLS - 20) / 2, "[%c] %s", options->grid_size == 4 ? 'X' : ' ', choices[i]);
            else if (i == 1)
                mvprintw(y_offset, (COLS - 20) / 2, "[%c] %s", options->grid_size == 5 ? 'X' : ' ', choices[i]);
            else
                mvprintw(y_offset, (COLS - 20) / 2, "%s", choices[i]);

            if (i == highlight)
                attroff(A_REVERSE);
        }

        choice = getch();

        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight < 0)
                    highlight = options_count - 1;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight >= options_count)
                    highlight = 0;
                break;
            case 10:
                if (highlight == 0)
                    options->grid_size = 4;
                else if (highlight == 1)
                    options->grid_size = 5;
                else if (highlight == 2)
                    return;
                break;
        }
        refresh();
    }
}

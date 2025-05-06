#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#include "display.h"
#include "libft.h"

static void draw_title(int start_y)
{
    char *title[] = {
        "2048",
        NULL
    };

    int title_width = 0;
    for (int i = 0; title[i] != NULL; i++)
    {
        int len = ft_strlen(title[i]);
        if (len > title_width)
            title_width = len;
    }

    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    int start_x = (term_width - title_width) / 2;

    for (int i = 0; title[i] != NULL; i++)
        mvprintw(start_y + i, start_x, "%s", title[i]);
}

static void draw_subtitle(int start_y)
{
    char *subtitle[] = {
        "WONG KAR WAI",
        NULL
    };

    int subtitle_width = 0;
    for (int i = 0; subtitle[i] != NULL; i++)
    {
        int len = ft_strlen(subtitle[i]);
        if (len > subtitle_width)
            subtitle_width = len;
    }

    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    int start_x = (term_width - subtitle_width) / 2;

    attron(A_BLINK);
    for (int i = 0; subtitle[i] != NULL; i++)
        mvprintw(start_y + i, start_x, "%s", subtitle[i]);
    attroff(A_BLINK);
}

static void animate_title()
{
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    int title_height = 1;
    int subtitle_height = 1;
    
    int start_y_title = (term_height - title_height - subtitle_height) / 2;
    int start_y_subtitle = start_y_title + title_height + 2;

    for (int offset = 10; offset >= -5; offset--)
    {
        clear();
        draw_title(start_y_title + offset);
        draw_subtitle(start_y_subtitle + offset);
        refresh();
        usleep(DELAY);
    }
}

static void draw_menu(int highlight)
{
    char *choices[] = { "Play", "Options", "Quit", NULL };
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    int start_y = (term_height) / 2 + 3;
    int start_x = (term_width - 10) / 2;

    for (int i = 0; choices[i] != NULL; i++)
    {
        if (i == highlight)
            attron(A_REVERSE);
        mvprintw(start_y + i * 2, start_x, "%s", choices[i]);
        if (i == highlight)
            attroff(A_REVERSE);
    }
}

int show_menu()
{
    int choice = 0;
    int c;
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    int start_y = (term_height) / 2 + 3;
    animate_title();
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);

    while (1)
    {
        clear();
        draw_title(start_y - 10);
        draw_subtitle(start_y - 7);
        draw_menu(choice);
        refresh();

        c = getch();
        switch (c)
        {
            case KEY_UP:
                choice--;
                if (choice < 0)
                    choice = 2;
                break;
            case KEY_DOWN:
                choice++;
                if (choice > 2)
                    choice = 0;
                break;
            case KEY_ENTR:
                return choice;
            case KEY_ESC:
                return 2;
        }
    }
}








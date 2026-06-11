#include <ncurses.h>
#include "tui.h"

void tui_init(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	timeout(100);
	keypad(stdscr, TRUE);
	clear();
	refresh();
}

void tui_shutdown(void)
{
    endwin();
}


void print_banner_tui(void)
{

mvprintw(0,0,"|        .__                       ");
mvprintw(1,0,"| ______ |  |  __ __  _________.__.");
mvprintw(2,0,"| \\____ \\|  | |  |  \\/  ___<   |  |"); 
mvprintw(3,0,"| |  |_> >  |_|  |  /\\___ \\ \\___  |");
mvprintw(4,0,"| |   __/|____/____//____  >/ ____|");
mvprintw(5,0,"| |__|                   \\/ \\/     ");


}

void print_menu_tui(const char *song, const char *list_type, double volume)
{
    print_banner_tui();

    mvprintw(6,0,"|");
    mvprintw(7,0,"##################################");
    mvprintw(8,0,"| S) Skip");
    mvprintw(9,0,"| U) Volume +5");
    mvprintw(10,0,"| D) Volume -5");
    mvprintw(11,0,"| P) Pause/Continue");
    mvprintw(12,0,"| Q) Quit");
    mvprintw(13,0,"| N) Normal Mode");
    mvprintw(14,0,"| R) Shuffle Mode");

    mvprintw(15,0,"##################################");

    move(16, 0);
    clrtoeol();
    mvprintw(16,0,"| Type: %s", list_type);

    move(17, 0);
    clrtoeol();
    mvprintw(17,0,"| Vol: %.0f%%", volume);

    move(18, 0);
    clrtoeol();
    mvprintw(18,0,"| Playing song: %.60s", song ? song : "unknown");

    mvprintw(19,0,"##################################");
}

#include <ncurses.h>
#include "tui.h"

void tui_init(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	timeout(35);
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

	mvprintw(0,0,"┌─────────────────────────────────────┐");
	mvprintw(1,0,"│         .__                         │");
	mvprintw(2,0,"│  ______ |  |  __ __  _________.__.  │");
	mvprintw(3,0,"│  \\____ \\|  | |  |  \\/  ___<   |  |  │"); 
	mvprintw(4,0,"│  |  |_> >  |_|  |  /\\___ \\ \\___  |  │");
	mvprintw(5,0,"│  |   __/|____/____//____  >/ ____|  │");
	mvprintw(6,0,"│  |__|                   \\/ \\/       │");
                    
                    
}

void print_menu_tui(const char *song, const char *list_type, double volume)
{
    print_banner_tui();

	mvprintw(7,0,  "│                                     │");
	mvprintw(8,0,  "│─────────────────────────────────────│");
    mvprintw(9,0,  "│ P) Pause/Continue                   │");
    mvprintw(10,0, "│ S) Skip                             │");
    mvprintw(11,0, "│ U) Volume +                         │");
    mvprintw(12,0, "│ D) Volume -                         │");
    mvprintw(13,0, "│ N) Normal Mode                      │");
    mvprintw(14,0, "│ R) Shuffle Mode                     │");
    mvprintw(15,0, "│                             Q) Quit │");
	mvprintw(16,0, "│─────────────────────────────────────│");
    move(17, 0);
    clrtoeol();
	mvprintw(17,0, "│ Type : %-27s  │", list_type);
    move(18, 0);
    clrtoeol();
	draw_volume(18, volume);
    move(19, 0);
    clrtoeol();
	mvprintw(19,0, "│ Song : %-27.27s  │", song);
    mvprintw(20,0, "└─────────────────────────────────────┘");
}


void draw_volume(int row, double volume)
{
    int bars = volume / 5;

    move(row, 0);
    clrtoeol();

    mvprintw(row, 0, "│ Vol: [");

    for(int i = 0; i < 20; i++)
        addch(i < bars ? '#' : '-');

    printw("] %3.0f%%    │", volume);
}

#ifndef TUI_H
#define TUI_H

void tui_init(void);
void tui_shutdown(void);
void print_menu_tui(const char *song, const char *list_type, double volume);
void print_banner_tui(void);
void draw_volume(int raw, double volume);


#endif

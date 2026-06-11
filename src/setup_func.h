#ifndef SETUP_FUNC_H
#define SETUP_FUNC_H

#include <stdbool.h>

void print_args(void);
bool path_setup(const char *path);
bool song_file_exist(void);
const char * get_home_dir(void);
const char *full_file_path(void);

#endif

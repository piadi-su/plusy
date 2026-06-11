#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>

// my files
#include "setup_func.h"
#include "types.h"


void
print_args(void)
{
	printf("\nusage:\n");
	printf("		the first time your run the program\n");
	printf("		run it with no args for setup\n");
	printf("-h, --help\n");
	printf("		show this.\n");
	printf("-v, --version\n");
	printf("		show the version of plusy.\n");
	printf("\n");
	printf("If you want to change the musci path delite the\n");
	printf(".playlist_path.conf	file in the HOME directory\n");

}



bool
path_setup(const char *path){
	


	DIR *m_dir = opendir(path);

	if(m_dir == NULL)
	{
		perror("opendir");
		return false;
	}

	FILE *song_dir = fopen(full_file_path(), "w");

	if (song_dir == NULL) {
		perror("fopen");
		closedir(m_dir);
		return false;
	}

	fprintf(song_dir,"%s\n",path);
		

	fclose(song_dir);
	closedir(m_dir);
	return true;
}

bool
song_file_exist(void)
{
	FILE *path_file = fopen(full_file_path(), "r");

	if(path_file == NULL){
		return false;
	}

	fclose(path_file);
	return true;
}

const char * 
get_home_dir(void)
{
    const char *home = getenv("HOME");

    if (home == NULL)
        return ".";

    return home;
}

const char *full_file_path(void)
{
	static char path[MAX_PATH_LEN];

	snprintf(
			path,
			sizeof(path),
			"%s/%s",
			get_home_dir(),
			CONFIG_FILE_NAME
			);

    return path;
}






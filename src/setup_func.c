#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#include <mpv/client.h>
#include <sys/select.h>
#include <ncurses.h>

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

}



bool
path_setup(const char *path){
	
	DIR *m_dir = opendir(path);

	if(m_dir == NULL)
	{
		perror("opendir");
		return false;
	}

	FILE *song_dir = fopen(SONG_FILE, "w");

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
	FILE *path_file = fopen(SONG_FILE, "r");

	if(path_file == NULL){
		return false;
	}

	fclose(path_file);
	return true;
}


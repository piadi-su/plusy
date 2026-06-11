#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <mpv/client.h>
#include <sys/select.h>
#include <ncurses.h>

// my files
#include "song_func.h"
#include "setup_func.h"
#include "types.h"


void 
skip_song(mpv_handle *mpvClient, full_playlist *playList)
{
	if(playList->mode == NORMAL_MODE)
	{
		playList->current++;

		if(playList->current >= playList->song_count)
		{
			playList->current = 0;
		}
	}
	else
	{
		playList->current = rand() % playList->song_count;
	}

    const char *cmd[] = {
        "loadfile",
        playList->songs[playList->current],
        NULL
    };
    mpv_command(mpvClient, cmd);


}

void
pause_continue(mpv_handle *mpvClient)
{

	const char *pc_cmd[] = {
		"cycle",
		"pause",
		NULL
	};

	mpv_command(mpvClient, pc_cmd);
}

void
volume_up(mpv_handle *mpvClient)
{
    double volume;

    mpv_get_property(
        mpvClient,
        "volume",
        MPV_FORMAT_DOUBLE,
        &volume);

    volume += 5;

    mpv_set_property(
        mpvClient,
        "volume",
        MPV_FORMAT_DOUBLE,
        &volume);
}


void
volume_down(mpv_handle *mpvClient)
{
    double volume;

    mpv_get_property(
        mpvClient,
        "volume",
        MPV_FORMAT_DOUBLE,
        &volume);

    volume -= 5;

    if (volume < 0)
        volume = 0;

    mpv_set_property(
        mpvClient,
        "volume",
        MPV_FORMAT_DOUBLE,
        &volume);
}

double get_volume(mpv_handle *mpvClient)
{
    double volume = 0;

    mpv_get_property(
        mpvClient,
        "volume",
        MPV_FORMAT_DOUBLE,
        &volume);

    return volume;
}

char *
current_song(mpv_handle *mpvClient)
{
    char *title = NULL;

    if (mpv_get_property(
            mpvClient,
            "media-title",
            MPV_FORMAT_STRING,
            &title) < 0)
    {
        return NULL;
    }

    return title;
}

bool 
load_playlist_path(char *playlist_path, size_t size)
{
	FILE *file_path = fopen(full_file_path(), "r");
	if(file_path == NULL)
	{
        perror("fopen");
		return false;
	}

	if(fgets(playlist_path, size, file_path) == NULL)
	{
		fclose(file_path);
		return false;
	}
	playlist_path[strcspn(playlist_path, "\n")] = '\0';

	fclose(file_path);
	return true;

}

void 
read_playlist_dir(const char *path, full_playlist *playList)
{
	DIR *playlist_dir = opendir(path);
	if(playlist_dir == NULL)
	{
		perror("opendir");
		return;
	}


	struct dirent *entry; // sara di dirent.h

	while ((entry = readdir(playlist_dir)) != NULL)
	{
		if (!strcmp(entry->d_name, ".") ||
				!strcmp(entry->d_name, ".."))
			continue;

		char full_path[1024];

		snprintf(
				full_path,
				sizeof(full_path),
				"%s/%s",
				path,
				entry->d_name
				);


		if (playList->song_count < MAX_SONGS)
		{
			playList->songs[playList->song_count] =
				strdup(full_path);

			playList->song_count++;
		}

	}

	closedir(playlist_dir);

}

void 
free_playlist(full_playlist  *playList)
{
	for (int i = 0; i < playList->song_count; i++)
	{
		free(playList->songs[i]);
	}
}






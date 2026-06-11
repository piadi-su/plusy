#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <mpv/client.h>
#include <sys/select.h>
#include <ncurses.h>
#include <locale.h>

// my files
#include "setup_func.h"
#include "song_func.h"
#include "types.h"
#include "tui.h"





// ----main----
int main(int argc , char *argv[]){
	
	setlocale(LC_ALL, "");
    setlocale(LC_NUMERIC, "C");

	int ret_c = 0;

	char path[512];
	char choice;
	char playlist_path[512];
	bool running = true;
	bool skip_lock = false;

	full_playlist playList = {0};
	playList.mode = NORMAL_MODE;

	char *currentSong = NULL;
	bool song_changed = true;
	bool ui_dirty = true;


	// setup / args
	if(!song_file_exist()){
		printf("insert the full path of your playlist\n");
		printf("es: /home/user/Music\n");
		printf("> ");
		
		if(fgets(path, sizeof(path), stdin) == NULL)
		{
			fprintf(stderr,"input error\n");
			return 1;
		}
		path[strcspn(path, "\n")] = '\0';
	

		if(path_setup(path)){
			printf("Path set successfully!\n");
		}
		return 0;
	}
	
	if (argc > 1 &&
		(!strcmp(argv[1], "-h") ||
		!strcmp(argv[1], "--help")))
	{
		print_args();
		return 0;
	}

	if (argc > 1 &&
		(!strcmp(argv[1], "-v") ||
		!strcmp(argv[1], "--version")))
	{
		printf("version: %.1f\n", VERSION);
		return 0;
	}
	
	
	// start mpv creation
	//create mpv client
	mpv_handle *mpvClient = mpv_create();
	if(mpvClient == NULL)
	{
		fprintf(stderr, "cannot create mpv context\n");
		ret_c = 1;
		goto cleanup;
	}

	//no video output
	mpv_set_option_string(mpvClient, "video", "no");

	//inizialize mpv client
	if (mpv_initialize(mpvClient) < 0) {
		fprintf(stderr, "cannot initialize mpv\n");
		ret_c = 1;
		goto cleanup;
	}
	
	
	if(!load_playlist_path(playlist_path, sizeof(playlist_path)))
	{
	
		fprintf(stderr, "can't open playlist path\n");
		ret_c = 1;
		goto cleanup;
			
	}


	// read all the playlist
	read_playlist_dir(playlist_path, &playList);

	if (playList.song_count == 0)
	{
		fprintf(stderr, "No songs found\n");
		ret_c = 1;
		goto cleanup;
	}

	const char *cmd[] = {
		"loadfile",
		playList.songs[playList.current],
		NULL
	};
	mpv_command(mpvClient, cmd);
	
	// --- start ncurces ---
	tui_init();

	// ---- song loop -----
	while(running)
	{
		mpv_event *event = mpv_wait_event(mpvClient, 0.5);

		if(event)
		{
			if(event->event_id == MPV_EVENT_END_FILE)
			{
				if(!skip_lock)
				{
					skip_song(mpvClient, &playList);
					skip_lock = true;
					ui_dirty = true;
					song_changed = true;
				}
			}

			if(event->event_id == MPV_EVENT_FILE_LOADED)
			{
				skip_lock = false;
				song_changed = true;
				ui_dirty = true;
			}
		}


		if(song_changed)
		{
			if(currentSong)
				mpv_free(currentSong);

			currentSong = current_song(mpvClient);
			song_changed = false;
		}


		choice = getch();

		if(choice != ERR)
		{
			ui_dirty = true;

			switch(choice)
			{
				case 'q':
					goto cleanup;

				case 'p':
					pause_continue(mpvClient);
					break;

				case 's':
					if(!skip_lock)
					{
						skip_song(mpvClient, &playList);
						skip_lock = true;
						song_changed = true;
					}
					break;

				case 'u':
					volume_up(mpvClient);
					break;

				case 'd':
					volume_down(mpvClient);
					break;

				case 'n':
					playList.mode = NORMAL_MODE;
					break;

				case 'r':
					playList.mode = SHUFFLE_MODE;
					break;
			}
		}


		if(ui_dirty)
		{
			print_menu_tui(
					currentSong ? currentSong : "unknown",
					playList.mode == NORMAL_MODE ? "normal" : "shuffle",
					get_volume(mpvClient)
					);

			ui_dirty = false;
		}
	}		
	
	
	cleanup:
		if (currentSong)
			mpv_free(currentSong);

		free_playlist(&playList);

		if (mpvClient)
			mpv_terminate_destroy(mpvClient);

		tui_shutdown();

		return ret_c;

}

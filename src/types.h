#ifndef TYPES_H
#define TYPES_H

// constants 
#define VERSION 1.0

#define MAX_SONGS 1000

#define CONFIG_FILE_NAME ".playlist_path.conf"
#define MAX_PATH_LEN 1024


// all structs

typedef enum{
	NORMAL_MODE,
	SHUFFLE_MODE
} playMode;


typedef struct {
	char *songs[MAX_SONGS];
	int song_count;
	int current;
	playMode mode;
}full_playlist;

#endif

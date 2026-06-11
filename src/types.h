#ifndef TYPES_H
#define TYPES_H

// constants 
#define SONG_FILE ".playlist_path.txt"
#define MAX_SONGS 1000
#define VERSION 1.0


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

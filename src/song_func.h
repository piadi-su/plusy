#ifndef SONG_FUNC_H
#define SONG_FUNC_H

#include <mpv/client.h>
#include "types.h"

void skip_song(mpv_handle *mpvClient, full_playlist *playList);
void pause_continue(mpv_handle *mpvClient);
void volume_up(mpv_handle *mpvClient);
void volume_down(mpv_handle *mpvClient);
double get_volume(mpv_handle *mpvClient);
char * current_song(mpv_handle *mpvClient);
bool load_playlist_path(char *playlist_path, size_t size);
void read_playlist_dir(const char *path, full_playlist *playList);
void free_playlist(full_playlist  *playList);



#endif

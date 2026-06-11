cmake_minimum_required(VERSION 3.16)

project(my-music C)

add_executable(my-music 
	src/main.c
	src/setup_func.c
	src/song_func.c
	src/tui.c
)

target_compile_options(my-music PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(my-music PRIVATE
    mpv
	ncurses
)

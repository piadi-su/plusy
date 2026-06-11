cmake_minimum_required(VERSION 3.16)

project(plusy C)

add_executable(plusy 
	src/main.c
	src/setup_func.c
	src/song_func.c
	src/tui.c
)

target_compile_options(plusy PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(plusy PRIVATE
    mpv
	ncurses
)

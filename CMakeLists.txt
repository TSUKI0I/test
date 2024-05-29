cmake_minimum_required(VERSION 3.26)
project(code C)

set(CMAKE_C_STANDARD 11)

add_library(code maze.c
        create_maze.c
        create_maze.h
        free_maze.h
        free_maze.c
        maze.h
        move.c
        move.h
        read_maze.c
        read_maze.h
)

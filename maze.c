/**
* @file maze.c
* @author Xinyue Wu
* @brief Code for the maze game for COMP1921 Assignment 2
*/
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "create_maze.h"
#include "free_maze.h"
#include "move.h"
#include "read_maze.h"
int main(int argc, char *argv[])
{
    // check args
    if(argc!=2){
        return EXIT_ARG_ERROR;
    }
    // set up some useful variables (you can rename or remove these if you want)
    coord *player;
    maze *maze = malloc(sizeof(*maze));
    FILE *file;
    // open and validate maze file
    file = fopen(argv[1],"r");
    if(!file){
        return EXIT_FILE_ERROR;
    }

    int width= get_width(file);
    int height= get_height(file);
    if(width==0||height==0){
        fclose(file);
        free(maze);
        return EXIT_MAZE_ERROR;
    }
    if (create_maze(maze, height, width) != 0) {
        fclose(file);
        free(maze);
        return EXIT_MAZE_ERROR;
    }

    read_maze(maze,file);
    fclose(file);

    player = &maze->start;
    // maze game loop
    char input;

    do{
        scanf("%c",&input);
        int ch = getchar();
        if (ch != '\n') {
            // Buffer clearing
            while ((ch = getchar()) != '\n' && ch != EOF);
            // Prompts the user to enter only one character
            printf("Invalid input. Please enter only one character.\n");
            continue;
        } else if(input=='Q'||input=='q'){
            printf("Quit the game.\n");
            break;
        }
        move(maze,player,input);
        if(has_won(maze,player)==1){
            break;
        }
    } while (1);
    // return, free, exit
    free_maze(maze);
    return EXIT_SUCCESS;
}


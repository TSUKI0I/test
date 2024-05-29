/**
* @file createMaze.c
* @author Xinyue Wu
* @brief Code for the maze game for COMP1921 Assignment 2
*/
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/**
 * @brief Initialise a maze object - allocate memory and set attributes
 *
 * @param this pointer to the maze to be initialised
 * @param height height to allocate
 * @param width width to allocate
 * @return int 0 on success, 1 on fail
 */
int create_maze(maze *this, int height, int width)
{
    // Dynamically apply a two-dimensional array
    // with a two-level pointer
    this->map = (char **)malloc(sizeof(char *) * height);
    if (this == NULL) {
        perror("Error: Memory allocation failed\n");
        return 1;
    }
    // Open space for each one-dimensional array
    for (int i = 0; i < height; i++)
    {
        this->map [i] = (char*)malloc(sizeof(char) * width);
        if (this->map [i] == NULL)
        {
            perror("Error: Memory allocation failed\n");
            return 1;
        }
    }

    this->height = height;
    this->width = width;

    return 0;
}







#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
/**
* @brief Free the memory allocated to the maze struct
*
* @param this the pointer to the struct to free
*/
void free_maze(maze *this)
{
    if(this!=NULL){
        for (int i = 0; i < this->height; i++)
        {
            free(this->map[i]);
            this->map[i] = NULL;
        }
        free(this->map);
        this->map = NULL;
    }
}

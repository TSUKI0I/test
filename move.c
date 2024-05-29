#include <stdio.h>
#include "maze.h"
/**
 * @brief Prints the maze out - code provided to ensure correct formatting
 *
 * @param this pointer to maze to print
 * @param player the current player location
 */
void print_maze(maze *this, coord *player)
{
    // make sure we have a leading newline
    printf("\n");
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            // decide whether player is on this spot or not
            if (player->x == j && player->y == i)
            {
                printf("X");
            }
            else
            {
                printf("%c", this->map[i][j]);
            }
        }
        // end each row with a newline.
        printf("\n");
    }
}

/**
 * @brief Validates and performs a movement in a given direction
 *
 * @param this Maze struct
 * @param player The player's current position
 * @param direction The desired direction to move in
 */


void move(maze *this, coord *player, char direction)
{
    int x = player->x;
    int y = player->y;
    switch (direction) {
        case 'W':
        case 'w':
            --y;
            break;
        case 'A':
        case 'a':
            --x;
            break;
        case 'S':
        case 's':
            ++y;
            break;
        case 'D':
        case 'd':
            ++x;
            break;
        case 'M':
        case 'm':
            print_maze(this,player);
            break;
        default:
            // print in the invalid way
            printf("Invalid input, please try again\n");
            break;
    }

    // If the player's next step will meet a wall
    if(this->map[y][x]=='#'){
        printf("You meet the wall\n");
    } else if ( x < 0 || x >= this->width || y < 0 || y >= this->height){
        printf("You off the edge of the map\n");
    } else{
        player->x = x;
        player->y = y;
    }

}

/**
 * @brief Check whether the player has won and return a pseudo-boolean
 *
 * @param this current maze
 * @param player player position
 * @return int 0 for false, 1 for true
 */
int has_won(maze *this, coord *player)
{
    int x = player->x;
    int y = player->y;
    if(this->map[y][x]=='E'){
        printf("You win the game");
        return 1;
    } else{
        return 0;
    }
}
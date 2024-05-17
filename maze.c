/**
 * @file maze.c
 * @author Xinyue Wu
 * @brief Code for the maze game for COMP1921 Assignment 2
 */
#include <stdio.h>
#include <stdlib.h>

#ifndef TOTAL_CODE_CW2_MAIN_H
#define TOTAL_CODE_CW2_MAIN_H

// defines for max and min permitted dimensions
#define MAX_DIM 100
#define MIN_DIM 5

// defines for the required auto grader exit codes
#define EXIT_SUCCESS 0
#define EXIT_ARG_ERROR 1
#define EXIT_FILE_ERROR 2
#define EXIT_MAZE_ERROR 3
#define EXIT_OTHER_ERROR 100
#define MAX_WIDTH 256

typedef struct Coord
{
    int x;
    int y;
} coord;

typedef struct Maze
{
    char **map;
    int height;
    int width;
    coord start;
    coord end;
} maze;

#endif //TOTAL_CODE_CW2_MAIN_H


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
        this->map [i] = (char*)malloc(sizeof(char) * height);
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

/**
 * @brief Validate and return the width of the maze file
 *
 * @param file the file pointer to check
 * @return int 0 for error, or a valid width (5-100)
 */
int get_width(FILE *file)
{
    int ch;
    int width = 0;
    while ((ch= fgetc(file))!='\n'&& ch != EOF){
        width++;
    }
    if(width>=MIN_DIM && width<=MAX_DIM){
        return width;
    } else{
        return 0;
    }

}

/**
 * @brief Validate and return the height of the maze file
 *
 * @param file the file pointer to check
 * @return int 0 for error, or a valid height (5-100)
 */
int get_height(FILE *file)
{
    fseek(file, 0, SEEK_SET);
    int ch;
    int height = 0;
    while ((ch= fgetc(file))!=EOF){
        if(ch=='\n'){
            height++;
        }
    }
    height++;
    if(height>=MIN_DIM && height<=MAX_DIM){
        return height;
    } else{
        return 0;
    }
}

/**
 * @brief read in a maze file into a struct
 *
 * @param this Maze struct to be used
 * @param file Maze file pointer
 * @return int 0 on success, 1 on fail
 */
int read_maze(maze *this, FILE *file)
{
    fseek(file, 0, SEEK_SET);
    int i = 0;
    int numS = 0;
    int numE = 0;
    int width = this->width;
    char line[MAX_WIDTH];
    // Reads the contents of the file line by line
    while (fgets(line, (int)sizeof (line), file) != NULL){
        for (int j = 0; j < width; ++j) {
            this->map[i][j]=line[j];
            // contain only specific char
            if(line[j]=='S'){
                this->start.x=i;
                this->start.y=j;
                numS++;
            }else if(line[j]=='E'){
                this->end.x=i;
                this->end.y=j;
                numE++;
            }else if (line[j]!=' '&&line[j]!='#'&&line[j]!='\n'){
                return 1;
            }
        }
        i++;
    }
    // Judge whether it has single 'S' and 'E'
    if(numS != 1 || numE!=1){
        return 1;
    }
    // Has every column the same height
    if(i!=this->height){
        return 1;
    }
    return 0;
}

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
        case 'Q':
        case 'q':
            printf("Quit the game.");
            break;
        case 'M':
        case 'm':
            print_maze(this,player);
            break;
        default:
            // print in the invalid way
            printf("");
    }

    // If the player's next step will meet a wall
    if(this->map[x][y]=='#'){
        printf("You meet the wall");
    } else if ( x < 0 || x >= this->width || y < 0 || y >= this->height){
        printf("You off the edge of the map");
    } else if(this->map[x][y]=='E'){
        printf("You win the game");
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
    if(this->map[x][y]=='E'){
        printf("You win the game");
        return 1;
    } else{
        return 0;
    }
}

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
        free(maze);
        fclose(file);
        return EXIT_MAZE_ERROR;
    }

    if (read_maze(maze, file) != 0) {
        free_maze(maze);
        free(maze);
        fclose(file);
        return EXIT_MAZE_ERROR;
    }
    fclose(file);
    // 将player放在S处
    player = &maze->start;
    print_maze(maze,player);

    // maze game loop

    // win

    // return, free, exit
    free_maze(maze);
    return EXIT_SUCCESS;
}


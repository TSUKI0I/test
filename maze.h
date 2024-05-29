#ifndef CODE_MAZE_H
#define CODE_MAZE_H
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




#endif //CODE_MAZE_H

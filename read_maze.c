#include "maze.h"
#include <stdio.h>

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
    int numS = 0;
    int numE = 0;
    fseek(file, 0, SEEK_SET);
    int ch;
    int height = 0;
    while ((ch= fgetc(file))!=EOF){
        if(ch=='\n'){
            height++;
        } else if (ch=='S'){
            numS++;
        } else if (ch=='E'){
            numE++;
        }else if (ch!=' '&&ch!='#'){
            return 0;
        }
    }
    height++;
    fseek(file, 0, SEEK_SET);
    // Check the maze is a rectangle
    int lineWidth = 0;
    int eachWidth[height];
    int i = 0;
    while ((ch= fgetc(file))!=EOF){
        if(ch=='\n'){
            eachWidth[i]=lineWidth;
            i++;
            lineWidth = 0;
        } else{
            lineWidth++;
        }
    }
    // The last line has no newline
    if(lineWidth > 0){
        eachWidth[i]=lineWidth;
    }
    for (int j = 0; j < height-1; ++j) {
        if(eachWidth[j]!=eachWidth[j+1]){
            return 0;
        }
    }
    // Judge whether it has single 'S' and 'E'
    if(numS != 1 || numE!=1){
        return 0;
    }
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
    int width = this->width;
    char line[MAX_WIDTH];
    // Reads the contents of the file line by line
    while (fgets(line, (int)sizeof (line), file) != NULL){
        for (int j = 0; j < width; ++j) {
            this->map[i][j]=line[j];
            // contain only specific char
            if(line[j]=='S'){
                this->start.x=j;
                this->start.y=i;
            }else if(line[j]=='E'){
                this->end.x=j;
                this->end.y=i;
            }
        }
        i++;
    }
    return 0;
}

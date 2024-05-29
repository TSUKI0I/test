
#ifndef CODE_MOVE_H
#define CODE_MOVE_H
void print_maze(maze *this, coord *player);
void move(maze *this, coord *player, char direction);
int has_won(maze *this, coord *player);
#endif //CODE_MOVE_H

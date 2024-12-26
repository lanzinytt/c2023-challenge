#ifndef INITIAL_H
#define INITIAL_H

typedef struct player{
    int x;
    int y;
}player;
player* p;
int* num;

int const MAXSIZE=60;
int direct[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
void game();
void jude_move(player* p,int* num);



#endif
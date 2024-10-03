#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <iostream>
#include <windows.h>
using namespace std;

#define WIDTH 20
#define HEIGHT 10

int direct[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int maze[HEIGHT][WIDTH] = {0};
int visited[HEIGHT][WIDTH] = {0};

int end_x;
int end_y;

typedef struct player{
    int x;
    int y;
}player;


void print_maze() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if(maze[i][j]==1){
                printf("%c ", ' ');
            }else if(maze[i][j]==0){
                printf("%c ",'#');
            }else{
                printf("%c ",'P');
            }
        }
        printf("\n");
    }
}

void generate_maze(int x, int y,int* stx,int* sty) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1,4);
    int directions[4][2] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
    maze[x][y] = 1;
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        if (new_x >= 1 && new_x < HEIGHT-1 && new_y >= 1 && new_y < WIDTH-1 && !visited[new_x][new_y]) {
            int dir = dis(gen) % 4;
            for (int j = 0; j < 4; j++) {
                int temp_x = x + directions[(dir + j) % 4][0];
                int temp_y = y + directions[(dir + j) % 4][1];
                if (temp_x == new_x && temp_y == new_y) {
                    maze[x + directions[(dir + j) % 4][0] / 2][y + directions[(dir + j) % 4][1] / 2] = 1;
                    *stx=x + directions[(dir + j) % 4][0] / 2;
                    *sty=y + directions[(dir + j) % 4][1] / 2;
                    generate_maze(new_x, new_y, stx, sty);
                    break;
                }
            }
        }
    }
}

void ClearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize =HEIGHT*4;
    DWORD count;
    for(short i=0;i<HEIGHT;i++){
        FillConsoleOutputCharacter(hConsole, ' ', dwConSize, {0, i}, &dwConSize);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, {0, i}, &dwConSize);
    }
    SetConsoleCursorPosition(hConsole, {0, 0});
}
player* initia(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1,WIDTH-1);
    int end_x = 0;
    int end_y = dis(gen);
    int start_x,start_y;
    generate_maze(end_x, end_y , &start_x, &start_y);
    player* p=(player*)malloc(sizeof(player));
    p->x=start_x;
    p->y=start_y;
    maze[start_x][start_y]=2;
    ClearConsole();
    print_maze();
    return p;
}
int move(){
    while (true) {
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            return(3);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            return(1);
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            return(2);
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            return(0);
        }

        Sleep(100); // 减少CPU使用率
    }
}
void judge_move(player* p){
    while(true){
        int cmd=move();
        int new_x=p->x+direct[cmd][0];
        int new_y=p->y+direct[cmd][1];
        if(maze[new_x][new_y] && new_x >=0 && new_x < HEIGHT && new_y >= 0 && new_y < WIDTH){
            maze[p->x][p->y]=1;
            p->x=new_x;
            p->y=new_y;
            maze[p->x][p->y]=2;
            break;
        }

    }
}
bool judge_win(player* p){
    extern int end_x;
    extern int end_y;
    if(p->x== end_x ){
        return false;
    }
    return true;
}
void game(player* p){
    bool flag=true;
    while(flag){
        judge_move(p);
        ClearConsole();
        print_maze();
        flag=judge_win(p);
        Sleep(100);
    }
    printf("good game!\n");
    system("pause");
}
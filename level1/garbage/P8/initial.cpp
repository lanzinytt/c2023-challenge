#include "initial.h"
#include <iostream>
#include <windows.h>
#include "tools.h"
#include "maze.h"
#include <algorithm>

using namespace std;

/*int Start(){
    bool flag=false;//确认是否确定
    int cmd;//监测按键
    int cho=0;
    while(not flag){
        ClearConsole(MAXSIZE);
        SetCursorPosition(MAXSIZE/2,MAXSIZE/8);
        cout<<"推箱子~";
        cmd=Move();
        switch (cmd){
            case 0:
            cho=(cho+1)%3;
                break;
            case 1:
            cho=(cho-1)%3;
                break;
            case -1:
            flag=true;
                break;
            default:
                break;
        }

        switch (cho){
            case 0:
                SetColor(1);
                SetCursorPosition(MAXSIZE/2,MAXSIZE/8*3);
                cout<<"   ez!!!  ";
                SetColor(3);
                SetCursorPosition(MAXSIZE/2,MAXSIZE/8*4);
                cout<<"  hard(  ";
                SetCursorPosition(MAXSIZE/2,MAXSIZE/8*5);
                cout<<"insane%$#@#";
                game(mapEasy);
                break;
            case 1:
                SetCursorPosition(MAXSIZE/2,MAXSIZE/8*3);
                cout<<"   ez!!!  ";
                SetColor(1);
                SetCursorPosition(MAXSIZE/2,MAXSIZE/8*4);
                cout<<"  hard(  ";
                SetColor(3);
                SetCursorPosition(MAXSIZE/2,MAXSIZE/8*5);
                cout<<"insane%$#@#";
                break;
            case 2:
                SetCursorPosition(MAXSIZE/2,MAXSIZE/8*3);
                cout<<"   ez!!!  ";
                SetCursorPosition(MAXSIZE/2,MAXSIZE/8*4);
                cout<<"  hard(  ";
                SetColor(1);
                SetCursorPosition(MAXSIZE/2,MAXSIZE/8*5);
                cout<<"insane%$#@#";
                SetColor(3);
                break;
            default:
                break;
        }
    }
    return cho;
}
*/
void jude_move(player* p,int* num){
    int dir;
    while(true){
        if(dir=Move()>0){
            int new_x=p->x+direct[dir][0];
            int new_y=p->y+direct[dir][1];
            if(mapMedium[new_x][new_y]==1){
                p->x=new_x;p->y=new_y;
                mapMedium[new_x][new_y]=3;
                mapMedium[p->x][p->y]=1;
            }else if(mapMedium[new_x][new_y]== 2){
                if(mapMedium[new_x+direct[dir][0]][new_y+direct[dir][1]]==1){
                    p->x=new_x;p->y=new_y;
                    mapMedium[new_x][new_y]=3;
                    mapMedium[p->x][p->y]=1;
                    mapMedium[new_x+direct[dir][0]][new_y+direct[dir][1]]=2;
                }else if(mapMedium[new_x+direct[dir][0]][new_y+direct[dir][1]]==4){
                    p->x=new_x;p->y=new_y;
                    mapMedium[new_x][new_y]=3;
                    mapMedium[p->x][p->y]=1;
                    *num-=1;    
                }
            }
            break;
        }
    }
}
void game(){
    bool flag=true;
    player* p;
    int num=2;
    p->x=5;p->y=2;//直接套搬中介地图

    while(flag){
        jude_move(p,&num);
        if(num==0){
            break;
        }
        ClearConsole(80);
        print_maze();
        Sleep(100);
    }
    printf("gg!!!");
}
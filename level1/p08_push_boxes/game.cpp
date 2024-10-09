#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include "tools.h"
#include <windows.h>
using json = nlohmann::json;
using namespace std;

typedef struct player{
    int x;
    int y;
}player;

void Easy(json j){
    int m_size=j["Easy"]["size"];
    int map[m_size][m_size];
    for(int i=0;i<m_size;i++){
        for(int k=0;k<m_size;k++){
            map[i][k]=j["Easy"]["map"][i][k];                    
        }
    }
    player* p=(player*)malloc(sizeof(player));
    p->x=3;
    p->y=2; 
    int score=10;
    while(true){
        ClearConsole(m_size+30);
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < m_size; j++) {
                switch (map[i][j])
                {
                case 0:
                    printf("%c ",'#');
                    break;
                case 1:
                    printf("%c ",' ');
                    break;
                case 2:
                    printf("%c ",'B');
                    break;
                case 3:
                    printf("%c ",'P');
                    break;
                case 4:
                    printf("%c ",'G');
                    break;
                default:
                    break;
                }
            }
            printf("\n");
        }
        SetCursorPosition(m_size,m_size/2);
        cout<<"score:"<<score;
        while(true){
            int cmd=move();
            int new_x=p->x+direct[cmd][0];
            int new_y=p->y+direct[cmd][1];
            if(map[new_x][new_y]==1){
                map[p->x][p->y]=1;
                p->x=new_x;
                p->y=new_y;
                map[p->x][p->y]=3;
                break;
            }else if(map[new_x][new_y]==2 && map[new_x+direct[cmd][0]][new_y+direct[cmd][1]]==1){
                map[p->x][p->y]=1;
                p->x=new_x;
                p->y=new_y;
                map[p->x][p->y]=3;
                map[new_x+direct[cmd][0]][new_y+direct[cmd][1]]=2;
                break;
            }else if(map[new_x][new_y]==2 && map[new_x+direct[cmd][0]][new_y+direct[cmd][1]]==4){
                map[p->x][p->y]=1;
                p->x=new_x;
                p->y=new_y;
                map[p->x][p->y]=3;
                score+=5;
                break;
            }

            Sleep(200);
        }
        score--;
        Sleep(100);
    }
    j["Easy"]["score"]=score;
    free(p);   
}

void normal(json j){
    int m_size=j["Normal"]["size"];
    int map[m_size][m_size];
    for(int i=0;i<m_size;i++){
        for(int k=0;k<m_size;k++){
            map[i][k]=j["Normal"]["map"][i][k];                    
        }
    }
    player* p=(player*)malloc(sizeof(player));
    p->x=3;
    p->y=2; 
    int score=10;
    while(true){
        ClearConsole(m_size+30);
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < m_size; j++) {
                switch (map[i][j])
                {
                case 0:
                    printf("%c ",'#');
                    break;
                case 1:
                    printf("%c ",' ');
                    break;
                case 2:
                    printf("%c ",'B');
                    break;
                case 3:
                    printf("%c ",'P');
                    break;
                case 4:
                    printf("%c ",'G');
                    break;
                default:
                    break;
                }
            }
            printf("\n");
        }
        SetCursorPosition(m_size,m_size/2);
        cout<<"score:"<<score;
        while(true){
            int cmd=move();
            int new_x=p->x+direct[cmd][0];
            int new_y=p->y+direct[cmd][1];
            if(map[new_x][new_y]==1){
                map[p->x][p->y]=1;
                p->x=new_x;
                p->y=new_y;
                map[p->x][p->y]=3;
                break;
            }else if(map[new_x][new_y]==2 && map[new_x+direct[cmd][0]][new_y+direct[cmd][1]]==1){
                map[p->x][p->y]=1;
                p->x=new_x;
                p->y=new_y;
                map[p->x][p->y]=3;
                map[new_x+direct[cmd][0]][new_y+direct[cmd][1]]=2;
                break;
            }else if(map[new_x][new_y]==2 && map[new_x+direct[cmd][0]][new_y+direct[cmd][1]]==4){
                map[p->x][p->y]=1;
                p->x=new_x;
                p->y=new_y;
                map[p->x][p->y]=3;
                score+=5;
                break;
            }

            Sleep(200);
        }
        score--;
        Sleep(100);
    }
    j["Normal"]["score"]=score;
    free(p); 
}

void hard(json j){
    int m_size=j["Hard"]["size"];
    int map[m_size][m_size];
    for(int i=0;i<m_size;i++){
        for(int k=0;k<m_size;k++){
            map[i][k]=j["Normal"]["map"][i][k];                    
        }
    }
    player* p=(player*)malloc(sizeof(player));
    p->x=3;
    p->y=2; 
    int score=10;
    while(true){
        ClearConsole(m_size+30);
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < m_size; j++) {
                switch (map[i][j])
                {
                case 0:
                    printf("%c ",'#');
                    break;
                case 1:
                    printf("%c ",' ');
                    break;
                case 2:
                    printf("%c ",'B');
                    break;
                case 3:
                    printf("%c ",'P');
                    break;
                case 4:
                    printf("%c ",'G');
                    break;
                default:
                    break;
                }
            }
            printf("\n");
        }
        SetCursorPosition(m_size,m_size/2);
        cout<<"score:"<<score;
        while(true){
            int cmd=move();
            int new_x=p->x+direct[cmd][0];
            int new_y=p->y+direct[cmd][1];
            if(map[new_x][new_y]==1){
                map[p->x][p->y]=1;
                p->x=new_x;
                p->y=new_y;
                map[p->x][p->y]=3;
                break;
            }else if(map[new_x][new_y]==2 && map[new_x+direct[cmd][0]][new_y+direct[cmd][1]]==1){
                map[p->x][p->y]=1;
                p->x=new_x;
                p->y=new_y;
                map[p->x][p->y]=3;
                map[new_x+direct[cmd][0]][new_y+direct[cmd][1]]=2;
                break;
            }else if(map[new_x][new_y]==2 && map[new_x+direct[cmd][0]][new_y+direct[cmd][1]]==4){
                map[p->x][p->y]=1;
                p->x=new_x;
                p->y=new_y;
                map[p->x][p->y]=3;
                score+=5;
                break;
            }

            Sleep(200);
        }
        score--;
        Sleep(100);
    }
    j["Hard"]["score"]=score;
    free(p); 
}
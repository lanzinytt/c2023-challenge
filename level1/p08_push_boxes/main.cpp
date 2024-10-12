#include "game.h"
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

json read_maze(int argc,char *argv[]){
    json j;
    if(argc ==1){
        ifstream jfile("./maze.json");
        jfile >> j;      
    }else if(argc==2){
        ifstream jfile(argv[1]);
        jfile >> j;
    }else{
        cout<<"WARNING";
    }
    return j;
}

int main(int argc,char *argv[]){
{    
    json j=read_maze(argc,argv);
    int m_size=j["Easy"]["size"];
    int map[m_size][m_size];
    for(int i=0;i<m_size;i++){
        for(int k=0;k<m_size;k++){
            map[i][k]=j["Easy"]["map"][i][k];                    
        }
    }
    int amount =j["Easy"]["amount"];
    player* p=(player*)malloc(sizeof(player));
    p->x=3;
    p->y=2; 
    int score=10;
    while(amount){
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
        cout<<"Score:"<<score;
        SetCursorPosition(m_size,m_size/2+1);
        cout<<"BestScore:"<<j["Easy"]["score"];
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
                amount--;
                break;
            }

            Sleep(200);
        }
        score--;
        Sleep(100);
    }
    SetCursorPosition(m_size/2,m_size/2+1);
    cout<<"DO YOU WANT TRY MORE?";
    system("pause");
    j["Easy"]["score"]=score;
    free(p);
    ofstream file("maze.json");
    file<<j<<endl;
}
{    
    json j=read_maze(argc,argv);
    int m_size=j["Normal"]["size"];
    int map[m_size][m_size];
    for(int i=0;i<m_size;i++){
        for(int k=0;k<m_size;k++){
            map[i][k]=j["Normal"]["map"][i][k];                    
        }
    }
    int amount =j["Normal"]["amount"];
    player* p=(player*)malloc(sizeof(player));
    p->x=3;
    p->y=2; 
    int score=10;
    while(amount){
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
        cout<<"Score:"<<score;
        SetCursorPosition(m_size,m_size/2+1);
        cout<<"BestScore:"<<j["Normal"]["score"];
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
                amount--;
                break;
            }

            Sleep(200);
        }
        score--;
        Sleep(100);
    }
    SetCursorPosition(m_size/2,m_size/2+1);
    cout<<"DO YOU WANT TRY MORE?";
    system("pause");
    j["Normal"]["score"]=score;
    free(p);
    ofstream file("maze.json");
    file<<j<<endl;
}
}
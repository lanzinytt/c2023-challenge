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
    json j=read_maze(argc,argv);
    Easy(j);
}
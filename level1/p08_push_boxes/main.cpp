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

int main(int argc,char *argv[]){
    Easy(argc,argv);
}
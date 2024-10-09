#ifndef GAME_H
#define GAME_H
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include "tools.h"
#include <windows.h>
using json = nlohmann::json;
using namespace std;
void Easy(json j);
void normal(int argc,char *argv[]);
void hard(int argc,char *argv[]);
#endif

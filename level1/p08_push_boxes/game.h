#ifndef GAME_H
#define GAME_H
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include "tools.h"
#include <windows.h>
using json = nlohmann::json;
using namespace std;
void easy(json j);
void normal(json j);
void hard(json j);
#endif

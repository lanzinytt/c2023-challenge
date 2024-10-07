#ifndef TOOLS_H
#define TOOLS_H

#include <windows.h>
#include <iostream>
#include "tools.h"

int direct[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};



void ClearConsole(int SIZE) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize =SIZE;
    DWORD count;
    for(short i=0;i<SIZE;i++){
        FillConsoleOutputCharacter(hConsole, ' ', dwConSize, {0, i}, &dwConSize);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, {0, i}, &dwConSize);
    }
    SetConsoleCursorPosition(hConsole, {0, 0});
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

void read_maze(){//读入读出
    
}

void SetCursorPosition(const int x, const int y)//设置光标位置
{
    COORD position;
    position.X = x * 2;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
#endif

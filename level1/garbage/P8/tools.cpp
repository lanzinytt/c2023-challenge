#include "tools.h"
#include <iostream>
#include <windows.h>
#include "maze.h"
int SIZE;

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

void SetCursorPosition(const int x, const int y)//设置光标位置
{
    COORD position;
    position.X = x * 2;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void print_maze() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            switch (mapMedium[i][j])
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
}

void SetColor(int colorID)//设置文本颜色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

void SetBackColor()//设置文本背景色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE |BACKGROUND_BLUE |BACKGROUND_GREEN |BACKGROUND_RED );
}

int Move(){
    while (true) {
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            return(0);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            return(1);
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            return(2);
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            return(3);
        }
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            return(-1);
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            return(-1);
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            return(-2);
        }
        Sleep(100); // 减少CPU使用率
    }
}
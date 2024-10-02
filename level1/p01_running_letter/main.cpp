#include <stdlib.h>
#include <windows.h>
#include <iostream>
using namespace std;

int ClearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 获取控制台屏幕的大小
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize =csbi.dwSize.X *csbi.dwSize.Y;  // 控制台的缓冲区大小
    DWORD count;
    // 填充整个屏幕缓冲区
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, {0, 0}, &dwConSize);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, {0, 0}, &dwConSize);
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, {0, 1}, &dwConSize);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, {0, 1}, &dwConSize);
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, {0, 2}, &dwConSize);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, {0, 2}, &dwConSize);
    
    SetConsoleCursorPosition(hConsole, {0, 0});
    if(csbi.dwSize.X>10){
        return csbi.dwSize.X;
    }else{
        return 10;
    }
}
int main (){
    int WIDTH=10;
    char str='A';
    int time=0;
    bool flag=true;
    int dis=0;
    while(time<1000){
        WIDTH=ClearConsole();
        if(flag){
            dis=time%WIDTH;
        }else{
            dis=WIDTH-time%WIDTH;
        }
        for(int i=0;i<dis;i++){
            cout<<' ';
        }
        cout<<str<<endl;
        time++;
        if(time%WIDTH==0){
            flag=not flag;
        }
        Sleep(100);
        
        
    }
    return 0;
}
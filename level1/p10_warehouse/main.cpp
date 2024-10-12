#include <iostream>
#include <nlohmann\json.hpp>
#include <fstream>
#include <string>
#include <typeinfo>
#include <windows.h>
using json=nlohmann::json;
using namespace std;
int const CONSIZE=100;

void SetCursorPosition(const int x, const int y)//设置光标位置
{
    COORD position;
    position.X = x * 2;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

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

json load_json(int argc,char *argv[],string filename){
    json j;
    if(argc==1){
        ifstream jfile(filename);
        jfile>>j;
    }else if(argc==2){
        ifstream jfile(argv[1]);
        jfile>>j;
    }else{
        cout<<"WARNING";
    }
    return j;
}

void save_json(json j,string filename){
    ofstream file(filename);
    file<<j<<endl;
}

void show_store(json j){
    cout<<"\tprize\tamount\n";
    printf("orange\t%d\t%d\n",(int)j["orange"]["prize"],(int)j["orange"]["amount"]);
    printf("apple\t%d\t%d\n",(int)j["apple"]["prize"],(int)j["apple"]["amount"]);
    printf("banana\t%d\t%d\n",(int)j["banana"]["prize"],(int)j["banana"]["amount"]);
}

void system(json j){
    while(true){
        string cmd,item;
        int num;
        ClearConsole(CONSIZE);
        SetCursorPosition(0,0);
        show_store(j["store"]["items"]);
        cout<<"Please input the cmd\ne.g. in orange 10 or quit\n";
        cin>>cmd;
        if(cmd=="quit"){
            cout<<"system quiting";
            exit(1);
        }else{
            cin>>item>>num;
            if(cmd=="in"){
                int temp=num+(int)j["store"]["items"][item]["amount"];
                j["store"]["items"][item]["amount"]=temp;
            }else if(cmd=="out"){
                int temp=(int)j["store"]["items"][item]["amount"]-num;
                j["store"]["items"][item]["amount"]=temp;
            }else{
                cout<<"undefine cmd!!";
                continue;
            }
        }    
    }
}

int main(int argc,char *argv[]) {
    string jsonname="./store.json";
    json j=load_json(argc,argv,jsonname);
    system(j);
//    save_json(j,jsonname);//不想破坏我自己手工创的jsonQAQ
    return 0;
}
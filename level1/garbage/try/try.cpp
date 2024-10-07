#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;
using namespace std;
int main(int argc,char *argv[]){
    json j;
    if(argc ==1){
        ifstream jfile("./tryj.json");
        jfile >> j;      
    }else if(argc==2){
        ifstream jfile(argv[1]);
        jfile >> j;
    }else{
        cout<<"WARNING";
        return -1;
    }
    for(int i=0;i<5;i++){
        for(int k=0;k<5;k++){
            cout<<j["mapEasy"][i][k]<<' ';
        }
        cout<<endl;
    }
}
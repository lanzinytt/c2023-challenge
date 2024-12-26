#ifndef GOBANGLOGIC_H
#define GOBANGLOGIC_H
#include <vector>
#include <cstdlib>
//int const FIVE=1000000;
//int const LIVEFOUR=10000;int const LIVETHREE=1000;int const LIVETWO=100;int const LIVEONE=10;
//int const DYINGFOUR=1000;int const DYINGTHREE=100;int const DYINGTWO=10;
/*
int const NOCHESS=0;
int const ONECHESS=1;
int const CONTI_TWO=10;int DIVID_TWO=10;int FARDIV_TWO=5;
int const CONTI_THREE=100;int DIVID_THREE=80;int FARDIV_THREE;

int const CONTI_FOUR=1000;int DIVID_FOUR=800; //这俩定义过？

int const FIVE=1000000;
*/
const int DEPTH=3;
const int NEARBY=4;
const int DIRECTIONS[4][2] = {{0, 1}, {1, 0}, {1, 1}, {-1, 1}};
struct Point{
    int x,y;
};

int const LAYER = 5;
int const BOARD_SIZE = 15;
int const INF=9999999;
static constexpr int results[]
    = { 0,5,5,80,5,60,100,500,5,20,80,500,100,500,8000,200000,5,10,//0-17
       20,600,50,600,500,8000,80,600,500,6000,500,8000,200000,10000000 };//18-31
/*
    * 十进制-二进制-得分
    * 0-00000-0-NOCHESS
    * 1-00001-5-ONECHESS
    * 2-00010-5-ONECHESS
    * 3-00011-80-CONTI_TWO
    * 4-00100-5-ONECHESS
    * 5-00101-60-DIVID_TWO
    * 6-00110-100-CONTI_TWO
    * 7-00111-500
    * 8-01000-5-ONECHESS
    * 9-01001-20
    * 10-01010-80-CONTI_TWO
    * 11-01011-500
    * 12-01100-100-CONTI_TWO
    * 13-01101-500
    * 14-01110-8000
    * 15-01111-100000
    * 16-10000-5-ONECHESS
    * 17-10001-10
    * 18-10010-20
    * 19-10011-600
    * 20-10100-50-DIVID_TWO
    * 21-10101-600
    * 22-10110-500
    * 23-10111-5000
    * 24-11000-80-CONTI_TWO
    * 25-11001-600
    * 26-11010-500
    * 27-11011-6000
    * 28-11100-500
    * 29-11101-5000
    * 30-11110-100000
    * 31-11111-MAX
*/
//对手返回负值，我方返回正值
//乘以1.1是为了偏重防守  转自CSDN大佬思路
void initBoard(int board[BOARD_SIZE][BOARD_SIZE]);

bool checkWin(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int color);

long long evaluateBoard(int board[BOARD_SIZE][BOARD_SIZE],int color,double bias);

void AIthink(int board[BOARD_SIZE][BOARD_SIZE],Point &last_pt);

int alphabeta(int board[BOARD_SIZE][BOARD_SIZE], int alpha, int beta, int depth, bool isMax, int color,std::vector<Point> blank_list,Point last_pt);

void dfstree(int MAXscore[LAYER],int board[BOARD_SIZE][BOARD_SIZE],int pointchoice[LAYER][2],int layer,int color);

#endif // GOBANGLOGIC_H

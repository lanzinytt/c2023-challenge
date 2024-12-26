#include "gobanglogic.h"
#include <QPoint>
#include <QDebug>


void initVector(std::vector<Point> &blank_list){
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            blank_list[i*BOARD_SIZE+j].x=i;
            blank_list[i*BOARD_SIZE+j].y=j;
        }
    }
}

void initBoard(int board[BOARD_SIZE][BOARD_SIZE]){
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

int compa(const Point &a,const Point &b){
    return std::abs(a.x-b.x)+std::abs(a.y-b.y);
}

void order(std::vector<Point> &blank_list,Point &last_pt){
    Point temp;
    for(int i=0;i<BOARD_SIZE*BOARD_SIZE;i++){
        temp=blank_list[i];
        if(compa(temp,last_pt)<=NEARBY){
            /*
            if(board[temp.x][temp.y]!=0){
                count++;
            }
            */
            blank_list.erase(blank_list.begin()+i);
            blank_list.insert(blank_list.begin(),temp);
        }
    }
}

long long evaluateBoard(int board[BOARD_SIZE][BOARD_SIZE],int color,double bias){
    double score=0;    bool is_only;           //总分 临时数据
    short k;        int now_color=0;        //是否唯一（不唯一则值为0） 计数  是否为正
    int chessList;  int px;     int py;     //录入棋子链 临时x与y

    for(int i=0;i<BOARD_SIZE-5;i++){    //001
        for(int j=5;j<BOARD_SIZE;j++){  //010
                                        //100
            is_only=true;   k=0;
            chessList=0;    px=i;   py=j;
            while(board[px][py]==0 && k<5){
                py=py+DIRECTIONS[3][0];px=px+DIRECTIONS[3][1];
                k++;
            }now_color=board[px][py];
            while(k<5 && is_only){
                if(now_color==-board[px][py]){
                    is_only=false;
                }
                chessList=chessList*2+(board[px][py]==0 ? 0:1);
                py=DIRECTIONS[3][0]+py;px=DIRECTIONS[3][1]+px;
                k++;
            }
            if(k==5 && is_only){
                score+=results[chessList]*(now_color*color)*(now_color==color ? 1:bias);//这里因为color是-1和1，所有相同是正，相反是减
            }
        }
    }

    for(int i=0;i<BOARD_SIZE-5;i++){      //100
        for(int j=0;j<BOARD_SIZE-5;j++){  //010
                                          //001
            is_only=true;   k=0;
            chessList=0;    px=i;   py=j;
            while(board[px][py]==0 && k<5){
                py=py+DIRECTIONS[2][0];px=px+DIRECTIONS[2][1];
                k++;
            }now_color=board[px][py];
            while(k<5 && is_only){
                if(now_color==-board[px][py]){
                    is_only=false;
                }
                chessList=chessList*2+(board[px][py]==0 ? 0:1);
                py=DIRECTIONS[2][0]+py;px=DIRECTIONS[2][1]+px;
                k++;
            }
            if(k==5 && is_only){
                score+=results[chessList]*(now_color*color)*(now_color==color ? 1:bias);//这里因为color是-1和1，所有相同是正，相反是减
            }
        }
    }

    for(int i=0;i<BOARD_SIZE-5;i++){      //000
        for(int j=0;j<BOARD_SIZE;j++){    //111
                                          //000
            is_only=true;   k=0;
            chessList=0;    px=i;   py=j;
            while(board[px][py]==0 && k<5){
                py=py+DIRECTIONS[1][1];px=px+DIRECTIONS[1][0];
                k++;
            }now_color=board[px][py];
            while(k<5 && is_only){
                if(now_color==-board[px][py]){
                    is_only=false;
                }
                chessList=chessList*2+(board[px][py]==0 ? 0:1);
                py=DIRECTIONS[1][1]+py;px=DIRECTIONS[1][0]+px;
                k++;
            }
            if(k==5 && is_only){
                score+=results[chessList]*(now_color*color)*(now_color==color ? 1:bias);//这里因为color是-1和1，所有相同是正，相反是减
            }
        }
    }

    for(int i=0;i<BOARD_SIZE;i++){        //010
        for(int j=0;j<BOARD_SIZE-5;j++){  //010
                                          //010
            is_only=true;   k=0;
            chessList=0;    px=i;   py=j;
            while(board[px][py]==0 && k<5){
                py=py+DIRECTIONS[0][1];px=px+DIRECTIONS[0][0];
                k++;
            }now_color=board[px][py];
            while(k<5 && is_only){
                if(now_color==-board[px][py]){
                    is_only=false;
                }
                chessList=chessList*2+(board[px][py]==0 ? 0:1);
                py=DIRECTIONS[0][1]+py;px=DIRECTIONS[0][0]+px;
                k++;
            }
            if(k==5 && is_only){
                score+=results[chessList]*(now_color*color)*(now_color==color ? 1:bias);//这里因为color是-1和1，所有相同是正，相反是减
            }
        }
    }

    return score;
}



void AIthink(int board[BOARD_SIZE][BOARD_SIZE],Point &last_pt){
    int bestX;int bestY;
    int bestscore=INF;
//    int near=NEARBY;
    int v;std::vector<Point> blank_list(BOARD_SIZE*BOARD_SIZE);

    initVector(blank_list);
    Point temp;

    order(blank_list,last_pt);

    for(int i=0;i<NEARBY*NEARBY*2*2;i++){
            temp=blank_list[i];
            if(board[temp.x][temp.y]!=0) continue;
            board[temp.x][temp.y]=-1;
            v=alphabeta(board,-INF,INF,DEPTH-1,true,1,blank_list,temp);
            board[temp.x][temp.y]=0;
            if(bestscore>v){
                bestscore=v;bestX=temp.x;bestY=temp.y;
            }

    }
    /*
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(board[i][j]!=0) continue;
            board[i][j]=-1;
            v=alphabeta(board,-INF,INF,DEPTH-1,true,1,blank_list,temp);
            board[i][j]=0;
            if(bestscore>v){
                bestscore=v;bestX=i;bestY=j;
            }
        }
    }
    */
    board[bestX][bestY]=-1;
    last_pt.x=bestX;last_pt.y=bestY;
}

int alphabeta(int board[BOARD_SIZE][BOARD_SIZE], int alpha, int beta, int depth, bool isMax, int color,std::vector<Point> blank_list,Point last_pt) {
    int score;
    if (depth == 0 || checkWin(board,last_pt.x,last_pt.y,color)) {
        if(checkWin(board,last_pt.x,last_pt.y,-1)){
            return color*INF;
        }
        return evaluateBoard(board,color,0.9);
    }
    Point temp;
    if (-isMax) {

        score = -INF;

        order(blank_list,last_pt);
        for(int i=0;i<NEARBY*NEARBY*2*2;i++){
            temp=blank_list[i];
            if(board[temp.x][temp.y]!=0) continue;
            board[temp.x][temp.y]=color;
            score=std::max(score,alphabeta(board,beta,alpha,depth-1,false,-color,blank_list,temp));
            board[temp.x][temp.y]=0;
            if(score > alpha){
                alpha=score;
            }
            if(beta <= alpha){
                break;
            }
        }
        /*
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == 0) {
                    board[i][j] = color;
                    score = std::max(score, alphabeta(board, alpha, beta, depth - 1, false, -color,blank_list,temp));
                    board[i][j] = 0;

                    if (score > alpha) {
                        alpha = score;
                    }
                    if (beta <= alpha) {
                        break; // 剪枝
                    }
                }
            }
        }
        */
    } else {
        score = INF;

        order(blank_list,last_pt);
        for(int i=0;i<NEARBY*NEARBY*2*2;i++){//改为near好调试

            temp=blank_list[i];
            if(board[temp.x][temp.y]!=0) continue;
            board[temp.x][temp.y]=color;
            score=std::min(score,alphabeta(board,beta,alpha,depth-1,true,-color,blank_list,temp));
            board[temp.x][temp.y]=0;
            if(score < beta){
                beta=score;
            }
            if(beta <= alpha){
                break;
            }
        }
        /*
        score = INF;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == 0) {
                    board[i][j] = -color;
                    score = std::min(score, alphabeta(board, alpha, beta, depth - 1, false, -color,blank_list,temp));
                    board[i][j] = 0;

                    if (score < beta) {
                        beta = score;
                    }
                    if (beta <= alpha) {
                        break; // 剪枝
                    }
                }
            }
        }
        */
    }

    return score;
}


bool checkWin(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int color) {

    for (int i = 0; i < 4; ++i) {
        int dx = DIRECTIONS[i][0];
        int dy = DIRECTIONS[i][1];
        int nx = x + dx, ny = y + dy;
        // 检查一个方向
        int count = 1; // 已经有一个棋子
        while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board[nx][ny] == color) {
            count++;
            nx += dx;
            ny += dy;
        }
        // 检查反方向
        nx = x - dx;
        ny = y - dy;
        while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board[nx][ny] == color) {
            count++;
            nx -= dx;
            ny -= dy;
        }
        if (count >= 5) {
            return true; // 找到五个连续的棋子
        }
    }
    return false;
}


/*bool isGameOver(int board[BOARD_SIZE][BOARD_SIZE],int x,int y){
    int px;int py;int nums;
    int direct[8][2]={{0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,-1},{1,-1},{-1,1}};
    for(int i=0;i<4;i++){
        px=x;py=y;nums=0;
        qDebug()<<i<<":";
        while((px+direct[i*2][0]>=0 && px+direct[i*2][0] >=0) && (px+direct[i*2][0]<BOARD_SIZE && py+direct[i*2][0]<BOARD_SIZE) &&
               board[px][py]==board[px+direct[i*2][0]][py+direct[i*2][1]] ){
            px=px+direct[i*2][0];py=px+direct[i*2][0];
            qDebug()<<board[px][py]<<" "<<board[px+direct[i*2][0]][py+direct[i*2][1]];
        }
        while((px+direct[i*2+1][0]>=0 && px+direct[i*2+1][0] >=0) && (px+direct[i*2+1][0]<BOARD_SIZE && py+direct[i*2+1][0]<BOARD_SIZE) &&
               board[px][py]==board[px+direct[i*2+1][0]][py+direct[i*2+1][1]]){
            px=px+direct[i*2+1][0];py=px+direct[i*2+1][0];
            nums+=1;
            qDebug()<<nums;
        }
        if(nums>=5){
            return true;
        }
    }
    return false;
}*/

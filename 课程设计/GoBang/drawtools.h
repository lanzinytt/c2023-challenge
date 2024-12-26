#ifndef DRAWTOOLS_H
#define DRAWTOOLS_H

#define BOARD_WIDTH 15  // 棋盘宽度，以格子数计
#define BOARD_HEIGHT 15 // 棋盘高度，以格子数计
#define CELL_SIZE 30   // 每个格子的大小，以像素计
#define START_POS_X 40   // 棋盘起始位置的X坐标
#define START_POS_Y 40   // 棋盘起始位置的Y坐标
#define SIGN_RANGE 10 //鼠标提示的范围
#define SIGN_SIZE 5
#define CHESS_SIZE 12
#define IS_BLACK 1
#define IS_WHITE -1

#include "gobanglogic.h"

#include <QPainter>
#include <QPointer>
#include <cmath>
#include <QDebug>

class Drawer{
public:
    static bool  clickreact(const QPoint &position ,int Board[BOARD_HEIGHT][BOARD_WIDTH],bool is_black,Point &last_pt){

        int px = position.x();int py = position.y();
        // 检查位置是否越界
        if (px - START_POS_X  < 0 || START_POS_X + BOARD_WIDTH * CELL_SIZE - px  < 0 ||
            py - START_POS_Y  < 0 || START_POS_Y + (BOARD_HEIGHT * CELL_SIZE+1) - py  < 0) {
            return false;
        }

        int gridX = (px - START_POS_X/8*5) / CELL_SIZE;
        int gridY = (py - START_POS_Y/8*5) / CELL_SIZE;

        if(Board[gridX][gridY]==IS_WHITE || Board[gridX][gridY]==IS_BLACK){
            return false;
        }
        if(is_black){
            Board[gridX][gridY]=IS_BLACK;
        }else{
            Board[gridX][gridY]=IS_WHITE;
        }
        last_pt.x=gridX;last_pt.y=gridY;
        if(checkWin(Board,gridX,gridY,(is_black ? IS_BLACK:IS_WHITE))){
            qDebug()<<"finish";
        }
        return true;
    }

    static  void drawBoard(QPainter &painter){
        for(int i=0;i<BOARD_WIDTH+1;i++){
            painter.drawLine(QPoint(START_POS_X+CELL_SIZE*i,START_POS_Y),QPoint(START_POS_X+CELL_SIZE*i,START_POS_Y+CELL_SIZE*BOARD_HEIGHT));
        }
        for(int i=0;i<BOARD_HEIGHT+1;i++){
            painter.drawLine(QPoint(START_POS_X,START_POS_Y+CELL_SIZE*i),QPoint(START_POS_X+CELL_SIZE*BOARD_WIDTH,START_POS_Y+CELL_SIZE*i));
        }
    }
    static void drawSign(QPainter &painter,const QPoint &position){

        int px = position.x();int py = position.y();
        // 检查位置是否越界
        if (px - START_POS_X  < 0 || START_POS_X + BOARD_WIDTH * CELL_SIZE - px  < 0 ||
            py - START_POS_Y  < 0 || START_POS_Y + (BOARD_HEIGHT * CELL_SIZE+1) - py  < 0) {
            return;
        }

        int gridX = (px - START_POS_X/8*5) / CELL_SIZE;
        int gridY = (py - START_POS_Y/8*5) / CELL_SIZE;

        QPoint actualPosition = QPoint(START_POS_X + gridX * CELL_SIZE  ,
                                       START_POS_Y + gridY * CELL_SIZE  );

        painter.drawEllipse(actualPosition, SIGN_SIZE, SIGN_SIZE);
    }

    static  void drawStone(QPainter &painter, const QPoint &position, bool isBlack) {
        painter.setBrush(isBlack ? Qt::black : Qt::white);
        painter.drawEllipse(position, CHESS_SIZE, CHESS_SIZE);
    }
    static  void drawStones(QPainter &painter,int Board[BOARD_WIDTH][BOARD_HEIGHT]){
        for(int i=0;i<BOARD_WIDTH;i++){
            for(int j=0;j<BOARD_HEIGHT;j++){
                if(Board[i][j]){
                    QPoint stonePos=QPoint(START_POS_X+i*CELL_SIZE,START_POS_Y+j*CELL_SIZE);
                    if(Board[i][j]==IS_BLACK){
                        drawStone(painter,stonePos,true);
                    }else if(Board[i][j]==IS_WHITE){
                        drawStone(painter,stonePos,false);
                    }else{
                        qDebug()<<"error chess color at"<<i<<","<<j;
                        exit(1);
                    }

                }
            }
        }
    }

};




#endif // DRAWTOOLS_H

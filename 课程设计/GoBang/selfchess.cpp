#include "selfchess.h"
#include "ui_selfchess.h"
#include <chrono>

selfchess::selfchess(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::selfchess)
{
    ui->setupUi(this);
    setWindowTitle("SelfChess && My debug tool");
    setWindowIcon(QIcon(":/interaction source/picture/R-C-001.ico"));
    this->setMouseTracking(true);
    this->setStyleSheet("background-color: #FFFFE0;");
    initBoard(Board);
    is_black=true;
    gameover=false;
    last_pt.x=-1;last_pt.y=-1;
}

selfchess::~selfchess()
{
    delete ui;
}

void selfchess::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 2));
    Drawer::drawBoard(painter);//绘制基本棋盘
    Drawer::drawSign(painter,mousePos);
    Drawer::drawStones(painter,Board);
}


void selfchess::mouseMoveEvent(QMouseEvent *event){
    mousePos=event->pos();       //获取鼠标位置
    update();
}

void selfchess::on_giveupButton_clicked()
{
    Widget *father=new Widget();
    this->close();
    father->show();
    delete this;
}
void selfchess::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        QPoint clickPos=event->pos();
        bool change =Drawer::clickreact(clickPos,Board,is_black,last_pt);
        if(change){
            is_black=!is_black;
            update();
            auto start = std::chrono::high_resolution_clock::now();
            ui->judge_chess->setText(QString::number(evaluateBoard(Board,1,0.05)));
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            ui->usedtime->setText(QString::number(duration.count()));
        }
    }
    if(last_pt.x!=-1 && event->button()==Qt::RightButton){
        Board[last_pt.x][last_pt.y]=0;
        is_black=!is_black;
        update();
        auto start = std::chrono::high_resolution_clock::now(); //runing time
        ui->judge_chess->setText(QString::number(evaluateBoard(Board,1,0.05)));
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        ui->usedtime->setText(QString::number(duration.count()));
    }
}


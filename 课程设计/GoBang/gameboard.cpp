#include "gameboard.h"
#include "ui_gameboard.h"


GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameBoard)
{
    ui->setupUi(this);
    setWindowTitle("AImaster!!");
    setWindowIcon(QIcon(":/interaction source/picture/R-C-001.ico"));
    this->setMouseTracking(true);
    this->setStyleSheet("background-color: #FFFFE0;");
    initBoard(Board);
    is_black=true;
    gameover=false;
    last_pt.x=-1;last_pt.y=-1;
    imga=new QImage;
    imgb=new QImage;
    imgc=new QImage;
    imga->scaled(100,100,Qt::KeepAspectRatio);
    imgb->scaled(100,100,Qt::KeepAspectRatio);
    imgc->scaled(100,100,Qt::KeepAspectRatio);
    imga->load(":/interaction source/picture/th.jpg");
    imgb->load(":/interaction source/picture/th2.png");
    imgc->load(":/interaction source/picture/th3.png");
    ui->label->setPixmap(QPixmap::fromImage(*imga));
}

GameBoard::~GameBoard()
{
    delete ui;
}

void GameBoard::on_giveupButton_clicked()
{
    Widget *father=new Widget();
    this->close();
    father->show();
    delete this;
}
void GameBoard::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black, 2));
    Drawer::drawBoard(painter);//绘制基本棋盘
    Drawer::drawSign(painter,mousePos);
    Drawer::drawStones(painter,Board);
}


void GameBoard::mouseMoveEvent(QMouseEvent *event){
    mousePos=event->pos();       //获取鼠标位置
    update();
}

void GameBoard::mousePressEvent(QMouseEvent *event){
    if(gameover==false && event->button()==Qt::LeftButton){
        QPoint clickPos=event->pos();
        bool change =Drawer::clickreact(clickPos,Board,is_black,last_pt);
        if(change){
            ui->label->setPixmap(QPixmap::fromImage(*imgb));
            repaint();
            gameover=checkWin(Board,last_pt.x,last_pt.y,1);

            if(gameover){
                msgBox.setText("呜呜呜，被打败了");
                msgBox.exec();
                ui->label->setPixmap(QPixmap::fromImage(*imgc));
                ui->giveupButton->setText("退出");
            }

            if(!gameover)AIthink(Board,last_pt);
            gameover=checkWin(Board,last_pt.x,last_pt.y,-1);

            if(gameover){
                msgBox.setText("还得练，杂鱼杂鱼~");
                msgBox.exec();
                ui->giveupButton->setText("退出");
            }
            if(!gameover) ui->label->setPixmap(QPixmap::fromImage(*imga));
            update();
        }   
    }

}





void GameBoard::on_peaceButton_clicked()
{   if(gameover) return;
    if(evaluateBoard(Board,-1,1)>0){
        msgBox.setText("AI觉得它胜券在握，并拒绝了和棋");
        msgBox.exec();
    }else{
        gameover=true;
        msgBox.setText("AI同意了和棋");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.exec();
        ui->giveupButton->setText("退出");
    }
}


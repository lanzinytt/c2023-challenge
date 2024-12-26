#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include <QMessageBox>

#include "widget.h"
#include "gobanglogic.h"
#include "drawtools.h"


namespace Ui {
class GameBoard;
}

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);
    ~GameBoard();
protected:
    void paintEvent(QPaintEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
private slots:
    void on_giveupButton_clicked();

    void on_peaceButton_clicked();

private:
    Ui::GameBoard *ui;
    QMessageBox msgBox;
    bool is_black;
    bool gameover;
    QImage* imga;
    QImage* imgb;
    QImage* imgc;
    QPoint mousePos;
    Point last_pt;
    int Board[BOARD_HEIGHT][BOARD_WIDTH];
};

#endif // GAMEBOARD_H

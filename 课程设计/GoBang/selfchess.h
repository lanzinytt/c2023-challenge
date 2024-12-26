#ifndef SELFCHESS_H
#define SELFCHESS_H

#include <QWidget>
#include <QMouseEvent>
#include "widget.h"
#include "gobanglogic.h"
#include "drawtools.h"

namespace Ui {
class selfchess;
}

class selfchess : public QWidget
{
    Q_OBJECT
public:
    explicit selfchess(QWidget *parent = nullptr);
    ~selfchess();
protected:
    void paintEvent(QPaintEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
private slots:
    void on_giveupButton_clicked();

private:
    Ui::selfchess *ui;
    QPoint  mousePos;
    Point   last_pt;
    int     Board[BOARD_WIDTH][BOARD_HEIGHT];
    bool    is_black;
    bool    gameover;
};

#endif // SELFCHESS_H

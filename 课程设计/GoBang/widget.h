#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "selfchess.h"
#include "gameboard.h"
#include "drawtools.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintboard();
private slots:
    void on_aiButton_clicked();

    void on_playselfButton_clicked();

private:
    Ui::Widget *ui;
    bool is_black=true;
    QPixmap pixmap;
    QImage* img;
    QPalette palette;
protected:

};
#endif // WIDGET_H

#ifndef AICHESSBOARD_H
#define AICHESSBOARD_H

#include <QWidget>

namespace Ui {
class Aichessboard;
}

class Aichessboard : public QWidget
{
    Q_OBJECT

public:
    explicit Aichessboard(QWidget *parent = nullptr);
    ~Aichessboard();

private:
    Ui::Aichessboard *ui;
};

#endif // AICHESSBOARD_H

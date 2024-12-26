#include "aichessboard.h"
#include "ui_aichessboard.h"

Aichessboard::Aichessboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Aichessboard)
{
    ui->setupUi(this);
}

Aichessboard::~Aichessboard()
{
    delete ui;
}

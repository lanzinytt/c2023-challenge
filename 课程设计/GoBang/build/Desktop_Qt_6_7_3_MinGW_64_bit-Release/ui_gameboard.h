/********************************************************************************
** Form generated from reading UI file 'gameboard.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEBOARD_H
#define UI_GAMEBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameBoard
{
public:
    QPushButton *giveupButton;
    QPushButton *peaceButton;
    QLabel *response;
    QLabel *label;

    void setupUi(QWidget *GameBoard)
    {
        if (GameBoard->objectName().isEmpty())
            GameBoard->setObjectName("GameBoard");
        GameBoard->resize(698, 555);
        giveupButton = new QPushButton(GameBoard);
        giveupButton->setObjectName("giveupButton");
        giveupButton->setGeometry(QRect(580, 260, 92, 31));
        peaceButton = new QPushButton(GameBoard);
        peaceButton->setObjectName("peaceButton");
        peaceButton->setGeometry(QRect(580, 340, 92, 28));
        response = new QLabel(GameBoard);
        response->setObjectName("response");
        response->setGeometry(QRect(490, 430, 191, 71));
        label = new QLabel(GameBoard);
        label->setObjectName("label");
        label->setGeometry(QRect(500, 20, 181, 191));
        label->setMinimumSize(QSize(181, 191));
        label->setMaximumSize(QSize(181, 191));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(GameBoard);

        QMetaObject::connectSlotsByName(GameBoard);
    } // setupUi

    void retranslateUi(QWidget *GameBoard)
    {
        GameBoard->setWindowTitle(QCoreApplication::translate("GameBoard", "Form", nullptr));
        giveupButton->setText(QCoreApplication::translate("GameBoard", "\350\256\244\350\276\223", nullptr));
        peaceButton->setText(QCoreApplication::translate("GameBoard", "\345\222\214\346\243\213", nullptr));
        response->setText(QString());
        label->setText(QCoreApplication::translate("GameBoard", "Picture", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameBoard: public Ui_GameBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEBOARD_H

/********************************************************************************
** Form generated from reading UI file 'selfchess.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELFCHESS_H
#define UI_SELFCHESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_selfchess
{
public:
    QPushButton *giveupButton;
    QLabel *judge_chess;
    QLabel *usedtime;

    void setupUi(QWidget *selfchess)
    {
        if (selfchess->objectName().isEmpty())
            selfchess->setObjectName("selfchess");
        selfchess->resize(659, 497);
        giveupButton = new QPushButton(selfchess);
        giveupButton->setObjectName("giveupButton");
        giveupButton->setGeometry(QRect(490, 120, 92, 28));
        judge_chess = new QLabel(selfchess);
        judge_chess->setObjectName("judge_chess");
        judge_chess->setGeometry(QRect(500, 50, 69, 19));
        usedtime = new QLabel(selfchess);
        usedtime->setObjectName("usedtime");
        usedtime->setGeometry(QRect(500, 30, 69, 19));

        retranslateUi(selfchess);

        QMetaObject::connectSlotsByName(selfchess);
    } // setupUi

    void retranslateUi(QWidget *selfchess)
    {
        selfchess->setWindowTitle(QCoreApplication::translate("selfchess", "Form", nullptr));
        giveupButton->setText(QCoreApplication::translate("selfchess", "\351\200\200\345\207\272", nullptr));
        judge_chess->setText(QCoreApplication::translate("selfchess", "0", nullptr));
        usedtime->setText(QCoreApplication::translate("selfchess", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class selfchess: public Ui_selfchess {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELFCHESS_H

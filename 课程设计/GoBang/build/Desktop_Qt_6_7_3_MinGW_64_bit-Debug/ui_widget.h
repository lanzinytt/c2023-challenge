/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *aiButton;
    QPushButton *playselfButton;
    QLabel *label;
    QLabel *pic;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(417, 375);
        aiButton = new QPushButton(Widget);
        aiButton->setObjectName("aiButton");
        aiButton->setGeometry(QRect(290, 280, 80, 50));
        aiButton->setMinimumSize(QSize(0, 50));
        playselfButton = new QPushButton(Widget);
        playselfButton->setObjectName("playselfButton");
        playselfButton->setGeometry(QRect(290, 190, 80, 50));
        playselfButton->setMinimumSize(QSize(0, 50));
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 120, 121, 41));
        pic = new QLabel(Widget);
        pic->setObjectName("pic");
        pic->setGeometry(QRect(130, 150, 69, 19));
        pic->raise();
        aiButton->raise();
        playselfButton->raise();
        label->raise();

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        aiButton->setText(QCoreApplication::translate("Widget", "AI", nullptr));
        playselfButton->setText(QCoreApplication::translate("Widget", "\345\215\225\344\272\272", nullptr));
        label->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:700;\">\344\272\224\345\255\220\346\243\213</span></p></body></html>", nullptr));
        pic->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

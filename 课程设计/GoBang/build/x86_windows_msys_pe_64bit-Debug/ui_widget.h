/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
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
    QLabel *label_2;
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(347, 311);
        aiButton = new QPushButton(Widget);
        aiButton->setObjectName("aiButton");
        aiButton->setGeometry(QRect(220, 240, 80, 50));
        aiButton->setMinimumSize(QSize(0, 50));
        playselfButton = new QPushButton(Widget);
        playselfButton->setObjectName("playselfButton");
        playselfButton->setGeometry(QRect(220, 170, 80, 50));
        playselfButton->setMinimumSize(QSize(0, 50));
        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 80, 121, 41));
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 190, 121, 20));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        aiButton->setText(QCoreApplication::translate("Widget", "AI", nullptr));
        playselfButton->setText(QCoreApplication::translate("Widget", "\345\215\225\344\272\272", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:700;\">\344\272\224\345\255\220\346\243\213</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\351\200\211\346\213\251\346\270\270\347\216\251\346\226\271\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

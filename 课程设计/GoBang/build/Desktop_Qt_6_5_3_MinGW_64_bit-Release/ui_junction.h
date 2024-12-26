/********************************************************************************
** Form generated from reading UI file 'junction.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JUNCTION_H
#define UI_JUNCTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_junction
{
public:
    QLabel *label;
    QPushButton *giveupButton;
    QPushButton *tryagainButton;

    void setupUi(QWidget *junction)
    {
        if (junction->objectName().isEmpty())
            junction->setObjectName("junction");
        junction->resize(230, 120);
        junction->setMinimumSize(QSize(230, 120));
        junction->setMaximumSize(QSize(230, 120));
        label = new QLabel(junction);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 10, 69, 19));
        giveupButton = new QPushButton(junction);
        giveupButton->setObjectName("giveupButton");
        giveupButton->setGeometry(QRect(10, 70, 92, 28));
        tryagainButton = new QPushButton(junction);
        tryagainButton->setObjectName("tryagainButton");
        tryagainButton->setGeometry(QRect(120, 70, 92, 28));

        retranslateUi(junction);

        QMetaObject::connectSlotsByName(junction);
    } // setupUi

    void retranslateUi(QWidget *junction)
    {
        junction->setWindowTitle(QCoreApplication::translate("junction", "Form", nullptr));
        label->setText(QString());
        giveupButton->setText(QString());
        tryagainButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class junction: public Ui_junction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JUNCTION_H

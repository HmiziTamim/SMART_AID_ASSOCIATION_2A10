/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTextEdit *textEdit;
    QLineEdit *message;
    QPushButton *send;
    QPushButton *bind;
    QLineEdit *nickname;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        textEdit = new QTextEdit(Widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(50, 80, 651, 341));
        message = new QLineEdit(Widget);
        message->setObjectName(QString::fromUtf8("message"));
        message->setGeometry(QRect(80, 450, 401, 28));
        send = new QPushButton(Widget);
        send->setObjectName(QString::fromUtf8("send"));
        send->setGeometry(QRect(490, 450, 83, 29));
        bind = new QPushButton(Widget);
        bind->setObjectName(QString::fromUtf8("bind"));
        bind->setGeometry(QRect(610, 450, 83, 29));
        nickname = new QLineEdit(Widget);
        nickname->setObjectName(QString::fromUtf8("nickname"));
        nickname->setGeometry(QRect(262, 30, 161, 28));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 30, 71, 20));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 460, 63, 20));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        send->setText(QCoreApplication::translate("Widget", "Envoyer", nullptr));
        bind->setText(QCoreApplication::translate("Widget", "Connecterr", nullptr));
        label->setText(QCoreApplication::translate("Widget", "Nickname", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "Message", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

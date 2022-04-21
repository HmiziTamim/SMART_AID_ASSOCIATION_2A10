/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *on;
    QPushButton *off;
    QPushButton *verifier;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLCDNumber *lcdbyte;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(578, 428);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(152, 166, 255);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        on = new QPushButton(centralwidget);
        on->setObjectName(QStringLiteral("on"));
        on->setGeometry(QRect(310, 150, 93, 28));
        off = new QPushButton(centralwidget);
        off->setObjectName(QStringLiteral("off"));
        off->setGeometry(QRect(310, 240, 93, 28));
        verifier = new QPushButton(centralwidget);
        verifier->setObjectName(QStringLiteral("verifier"));
        verifier->setGeometry(QRect(310, 70, 93, 28));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 75, 201, 21));
        label->setStyleSheet(QStringLiteral("font: 16pt \"MS Shell Dlg 2\";"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 150, 191, 31));
        label_2->setStyleSheet(QStringLiteral("font: 16pt \"MS Shell Dlg 2\";"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 240, 221, 31));
        label_3->setStyleSheet(QStringLiteral("font: 16pt \"MS Shell Dlg 2\";"));
        lcdbyte = new QLCDNumber(centralwidget);
        lcdbyte->setObjectName(QStringLiteral("lcdbyte"));
        lcdbyte->setGeometry(QRect(430, 350, 64, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 578, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        on->setText(QApplication::translate("MainWindow", "on", Q_NULLPTR));
        off->setText(QApplication::translate("MainWindow", "off", Q_NULLPTR));
        verifier->setText(QApplication::translate("MainWindow", "verifier", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Verifier la Carte:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Ouvrir la porte:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Fermer la porte:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

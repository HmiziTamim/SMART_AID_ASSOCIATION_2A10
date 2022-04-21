#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "evenement.h"
#include <QModelIndex>
#include<QMessageBox>
#include<QIntValidator>
#include<QModelIndex>
#include <QRegExpValidator>
#include<QSqlQuery>
#include <QPdfWriter>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QPrinter>

#include <QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QUrl>
//#include <Qtpositioning>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_le_supprimer_clicked();



    void on_tab_evenement_activated(const QModelIndex &index);











    void on_tabWidget_currentChanged(int index);

    void on_tabWidget_tabBarClicked(int index);

    void on_pb_ajouterevent_clicked();

    void on_pb_changer_clicked();

    void on_pb_modifierevent_clicked();

    void on_pb_triparidevent_clicked();

    void on_pb_triparnomevent_clicked();

    void on_pb_pdfevent_clicked();

    void on_pb_rechercheevent_clicked();

private:
    Ui::MainWindow *ui;
    Evenement E ;
};

#endif // MAINWINDOW_H

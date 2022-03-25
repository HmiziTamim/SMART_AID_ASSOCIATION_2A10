#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QIntValidator>
#include <QMessageBox>
#include <QMainWindow>
#include <QApplication>
#include <QtDebug>
#include <QDate>
#include <QRegExpValidator>
#include "patient.h"
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
    void on_pushButtonQuitter_clicked();

    void on_pushButtonAjouter_clicked();

    void on_pushButtonSUPP_clicked();

    void on_pushButtonModifier_clicked();

    void on_pb_triparid_clicked();

    void on_pb_triparnom_clicked();

    void on_pushButtonRECHERCHE_clicked();

    void on_pushButton_clicked();

    void on_pushButtonSTAT_clicked();

    void on_pushButtonRECHERCHE_2_clicked();

    void on_pushButtonRECHERCHE_3_clicked();



    void on_pb_triparprenom_clicked();

private:
    Ui::MainWindow *ui;
    Patient P;
};

#endif // MAINWINDOW_H

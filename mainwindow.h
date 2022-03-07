#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include <QMainWindow>
#include "employe.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();

    void on_pb_supp_clicked();

    void on_pushButton_2_clicked();

    void on_quitter_clicked();

    void on_pushButton_clicked();



    void on_tab_employe_activated(const QModelIndex &index);


    void on_tri_cb_clicked();


    void on_pb_rech_clicked();

private:
    Ui::MainWindow *ui;
    Employe e;
};
#endif // MAINWINDOW_H

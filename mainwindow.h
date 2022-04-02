#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include <QMainWindow>
#include "employe.h"
#include<QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QTcpSocket;
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

    void on_pdf_clicked();


    void on_stat_clicked();

    void on_le_rech_textChanged(const QString &arg1);

    void on_ajouter_image_clicked();


    void on_send_clicked();

    void on_bind_clicked();

private:
    Ui::MainWindow *ui;
    Employe e;
     QTcpSocket *mSocket;
};
#endif // MAINWINDOW_H

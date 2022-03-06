#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stock.h"
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
    void on_pushButton_clicked();

    void on_tri_alphabetique_stock_clicked();

    void on_tri_desc_id_clicked();

    void on_tri_asc_id_clicked();

    void on_pb_supp_clicked();

    void on_pb_modifier_clicked();

    void on_recherche_Stock_clicked();

private:
    Ui::MainWindow *ui;
    stock S;  //ob+att
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "stock.h"

#include "historique.h"
#include "histosupp.h"
#include "histomod.h"
#include "qrcode.h"
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

    void on_Pdf_clicked();

    void on_stat_clicked();

    void on_qrCode_clicked();

    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();

private:
    Ui::MainWindow *ui;
    stock S;  //ob+att

     historique tm;
     histosupp ts;
     histomod hm;

};

#endif // MAINWINDOW_H

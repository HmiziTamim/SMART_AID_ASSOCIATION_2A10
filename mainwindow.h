#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "stock.h"

#include "historique.h"

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
    void on_ajouterp_clicked();

    void on_tri_alphabetique_stockpr_clicked();

    void on_tri_desc_idpr_clicked();

    void on_tri_asc_idpr_clicked();

    void on_pb_supppr_clicked();

    void on_pb_modifierpr_clicked();

    void on_recherche_Stockpr_clicked();

    void on_Pdfpr_clicked();

    void on_statpr_clicked();

    void on_qrCodepr_clicked();

    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();

    void on_rech_nompr_clicked();

private:
    Ui::MainWindow *ui;
    stock S;  //ob+att

    historique H;

};

#endif // MAINWINDOW_H

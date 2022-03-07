#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "evenement.h"
#include <QModelIndex>
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
    void on_pb_ajouter_clicked();

    void on_le_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_tab_evenement_activated(const QModelIndex &index);

    void on_pb_recherche_clicked();

    void on_pb_triparnom_clicked();

    void on_pb_triparid_clicked();

private:
    Ui::MainWindow *ui;
    Evenement E ;
};

#endif // MAINWINDOW_H

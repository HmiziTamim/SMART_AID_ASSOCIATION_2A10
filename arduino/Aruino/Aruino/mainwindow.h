#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "arduino.h"
#include "client.h"
#include <QMainWindow>

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

    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
    // ce slot est lancé à chaque réception d'un message de Arduino

    void on_verifier_clicked();   // bouton ON
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;

    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
    client C;
};

#endif // MAINWINDOW_H

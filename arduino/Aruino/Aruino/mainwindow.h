#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "arduino.h"
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void updateGUI(QByteArray data);

private slots:
    void on_on_clicked();

    void on_off_clicked();

    void on_verifier_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    arduino *arduinoc;
    client C;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "volontaire.h"
#include "smtp.h"
#include <QSerialPort>
#include <QSerialPortInfo>

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

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_le_rech_textChanged();

    void on_pb_tri_nom_clicked();

    void on_pb_tri_prenom_clicked();

    void on_pb_tri_age_clicked();

    void on_pb_pdf_clicked();

    int on_pb_cf_clicked();

    void on_comboBox_3_currentTextChanged(const QString &arg1);


    void on_pb_mail_clicked();
    void mailSent(QString status);

    void on_pushButton_3_clicked();


    void on_pb_stat_clicked();

    void on_pb_stat_2_clicked();

      void serial_read();

      void update_dist(const QString );

      void on_radioButton_clicked();

      void on_radioButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Volontaire V;
    QSerialPort *serial;
    QString portname;
    quint16 vendorId;
    quint16 productId;
    bool arduino_available;
    void arduino_init();

    QString test;
    QString temperature;
    bool tem;

    QByteArray serialData;
    QString serialBuffer;
};

#endif // MAINWINDOW_H

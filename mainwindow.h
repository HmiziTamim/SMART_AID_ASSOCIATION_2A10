#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include <QMainWindow>
#include "employe.h"
#include "volontaire.h"
#include"patient.h"
#include"evenement.h"
#include"stock.h"
#include "historique.h"
#include "qrcode.h"
#include "arduino.h"

#include "smtp.h"
#include <QSerialPort>
#include <QSerialPortInfo>
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

    //******************* KOUSSAY *******************
    void on_ajouter_clicked();

    void on_pb_supp_clicked();

    void on_pushButton_10_clicked();

    void on_quitter_clicked();

    void on_pushButton_4_clicked();

    void on_tab_employe_activated(const QModelIndex &index);

    void on_tri_cb_clicked();

    void on_pb_rech_clicked();

    void on_pdf_clicked();

    void on_stat_clicked();

    void on_le_rech_textChanged(const QString &arg1);

    void on_ajouter_image_clicked();

    void on_send_clicked();

    void on_bind_clicked();


   //******************* Boutton *******************
      void on_pb_kouss_clicked();
      void on_pb_amine_clicked();
      void on_pb_larbi_clicked();
      void on_pb_tamim_clicked();
      void on_pb_sarr_clicked();
      void on_toolButton_2_pressed();
      void on_toolButton_pressed();
      void on_toolButton_3_pressed();
      void on_toolButton_4_pressed();


    //******************* lim3allem *******************

    void on_pb_ajouter_clicked();

       void on_pb_supprimer_clicked();

       void on_pb_modifier_clicked();

       void on_comboBox_3_currentTextChanged(const QString &arg1);


       void on_pushButton_clicked();

       void on_pushButton_2_clicked();

       void on_le_rech_2_textChanged();

       void on_pb_tri_nom_clicked();

       void on_pb_tri_prenom_clicked();

       void on_pb_tri_age_clicked();

       void on_pb_pdf_clicked();

       int on_pb_cf_clicked();

       void on_comboBox_4_currentTextChanged(const QString &arg1);


       void on_pb_mail_clicked();
       void mailSent(QString status);

       void on_pushButton_3_clicked();


       void on_pb_stat_clicked();

       void on_pb_stat_2_clicked();

       void serial_read();

       void update_dist(const QString );

       void on_radioButton_clicked();

       void on_radioButton_2_clicked();


      //******************* Tamim *******************

       void on_tpushButtonAjouter_4_clicked();

       void on_tpushButtonSUPP_4_clicked();

       void on_tpushButtonModifier_4_clicked();

       void on_tpb_triparid_4_clicked();


       void on_tpushButtonRECHERCHE_10_clicked();

       void on_tpushButton_4_clicked();

       void on_tpushButtonSTAT_4_clicked();

       void on_tpushButtonRECHERCHE_11_clicked();

       void on_tpushButtonRECHERCHE_12_clicked();


       void on_tpb_triparnom_4_clicked();
       void on_tpb_triparprenom_4_clicked();

       void on_radioButton_30_toggled();

       void on_radioButton_31_toggled();

       void on_radioButton_29_toggled();

       void on_radioButton_28_toggled();

       void on_radioButton_27_toggled();

       void on_radioButton_33_toggled();

       void on_radioButton_32_toggled();

       void on_radioButton_34_toggled();

      //******************* Larbi *******************

       void on_le_supprimer_clicked();

       void on_tab_evenement_activated(const QModelIndex &index);

       void on_tabWidget_2_currentChanged();

       void on_tabWidget_2_tabBarClicked();

       void on_pb_ajouterevent_clicked();

       void on_pb_changer_clicked();

       void on_pb_modifierevent_clicked();

       void on_pb_triparidevent_clicked();

       void on_pb_triparnomevent_clicked();

       void on_pb_pdfevent_clicked();

       void on_pb_rechercheevent_clicked();


       void on_signup_clicked();

       void on_login_clicked();

       void on_acc_clicked();

       void on_returnlogin_clicked();

       void on_logout_clicked();

       //*******************Sarra*******************

         void on_ajouterp_5_clicked();

         void on_tri_alphabetique_stockpr_5_clicked();

         void on_tri_desc_idpr_5_clicked();

         void on_tri_asc_idpr_5_clicked();

         void on_pb_supppr_5_clicked();

         void on_pb_modifierpr_5_clicked();

         void on_recherche_Stockpr_5_clicked();

         void on_Pdfpr_5_clicked();

         void on_statpr_5_clicked();

         void on_qrCodepr_5_clicked();

         void NumPressed();
         void MathButtonPressed();
         void EqualButtonPressed();
         void ChangeNumberSign();

         void on_rech_nompr_5_clicked();

         void update_label();

         void on_verifier_clicked();   // bouton ON

           void on_pushButton55_clicked();



private:
    Ui::MainWindow *ui;
    Employe e;
     QTcpSocket *mSocket;
     Volontaire V;
     Patient P;
     Evenement E ;

     stock S;
     historique H;
     QByteArray data; // variable contenant les données reçues
     arduino A; // objet temporaire

        QSerialPort *serial;
        QString portname;
        quint16 vendorId;
        quint16 productId;
        bool arduino_available;
        void arduino_init();


        QString test;
        QString temperature;
        bool tem;
        bool t;

        QByteArray serialData;
        QString serialBuffer;
};
#endif // MAINWINDOW_H

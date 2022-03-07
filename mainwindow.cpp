#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "employe.h"
#include <QString>
#include<QMessageBox>
#include<QIntValidator>
#include <QtGui>
#include<QSqlQuery>
#include <QRegExpValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_cin->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_tel->setValidator(new QIntValidator(0, 99999999, this));

    QRegExp rxnom("\\b[a-zA-Z]{2,50}\\b");
        QRegExpValidator *valinom =new QRegExpValidator(rxnom,this);
        ui->le_nom->setValidator(valinom);
        ui->le_prenom->setValidator(valinom);
        ui->le_nat->setValidator(valinom);
        ui->le_etat->setValidator(valinom);
        ui->le_adresse->setValidator(valinom);
        ui->le_mod_nom->setValidator(valinom);
        ui->le_mod_prenom->setValidator(valinom);
        ui->le_mod_nat->setValidator(valinom);
        ui->le_mod_etat->setValidator(valinom);
        ui->le_mod_adresse->setValidator(valinom);
    QRegExp rxEmail("\\b[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4}\\b");
    QRegExpValidator *valiEmail =new QRegExpValidator(rxEmail,this);
    ui->le_email->setValidator(valiEmail);

    ui->tab_employe->setModel(e.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    int cin=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString nat=ui->le_nat->text();
    QString etat=ui->le_etat->text();
    QDate naiss=ui->le_date->date();
    QString email=ui->le_email->text();
    QString adresse=ui->le_adresse->text();
    int tel=ui->le_tel->text().toInt();
    QString sexe=ui->comboBox->currentText();
    if(email.contains(QRegExp("\\b[a-zA-Z0-9.%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4}\\b")))
    {
    Employe e(cin,nom,prenom,nat,etat,email,naiss,adresse,tel,sexe);
    bool test=e.ajouter();
       if(test)
       {
        QMessageBox::information(nullptr, QObject::tr("OK"),
               QObject::tr("Ajout effectué\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_employe->setModel(e.afficher());
       }
       else
       {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Ajout non effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
       }
}else
    {
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
             QObject::tr("L'email doit contenir @\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_supp_clicked()
{

    int cin =ui->le_id_supp->text().toInt();
   Employe e1; e1.setcin(cin);

   bool test=e1.supprimer(e1.getcin());
   if(test)
   {
    QMessageBox::information(nullptr, QObject::tr("OK"),
           QObject::tr("Suppression effectué\n"
                       "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_employe->setModel(e.afficher());
   }
   else
   {
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
            QObject::tr("Suppression n'est pas effectué\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
   }


}



void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}

void MainWindow::on_quitter_clicked()
{
    this->close();
}


void MainWindow::on_pushButton_clicked()
{
    int cin=ui->le_mod_cin->text().toInt();
    QString nom=ui->le_mod_nom->text();
    QString prenom=ui->le_mod_prenom->text();
    QString nat=ui->le_mod_nat->text();
    QString etat=ui->le_mod_etat->text();
    QString email=ui->le_mod_email->text();
    QDate naiss=ui->le_mod_date->date();
    QString adresse=ui->le_mod_adresse->text();
    int tel=ui->le_mod_tel->text().toInt();
    QString sexe=ui->comboBox_mod->currentText();
    Employe e(cin,nom,prenom,nat,etat,email,naiss,adresse,tel,sexe);
    bool test=e.modifier(cin);
       if(test)
       {
        QMessageBox::information(nullptr, QObject::tr("OK"),
               QObject::tr("Modification effectué\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_employe->setModel(e.afficher());
       }
       else
       {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Modification non effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
       }
}

void MainWindow::on_tab_employe_activated(const QModelIndex &index)
{
    QString val=ui->tab_employe->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from employe where cin='"+val+"' or nom='"+val+"' or prenom='"+val+"' or nat='"+val+"' or etat='"+val+"' or email='"+val+"' or adresse='"+val+"' or tel='"+val+"'");
    if(qry.exec())
    {
    while(qry.next())
    {
        ui->le_mod_cin->setText((qry.value(0).toString()));
        ui->le_id_supp->setText(qry.value(0).toString());
        ui->le_mod_nom->setText(qry.value(1).toString());
        ui->le_mod_prenom->setText(qry.value(2).toString());
        ui->le_mod_nat->setText(qry.value(3).toString());
        ui->le_mod_etat->setText(qry.value(5).toString());
        ui->le_mod_email->setText(qry.value(4).toString());
        ui->le_mod_adresse->setText(qry.value(7).toString());
        ui->le_mod_tel->setText(qry.value(8).toString());
    }
    }
}


void MainWindow::on_tri_cb_clicked()
{
    QString tri=ui->cb_tri->currentText();
    if(tri=="Nom")
         ui->tab_employe->setModel(e.triNom());
    else if(tri=="Prenom")
         ui->tab_employe->setModel(e.triprenom());
    else if(tri=="CIN")
        ui->tab_employe->setModel(e.tricin());
    else if(tri=="Telephone")
        ui->tab_employe->setModel(e.tritel());
    else if(tri=="Adresse")
        ui->tab_employe->setModel(e.triadresse());
    else if(tri=="Email")
        ui->tab_employe->setModel(e.triemail());
    else if(tri=="Nationnalité")
        ui->tab_employe->setModel(e.trinat());

}

void MainWindow::on_pb_rech_clicked()
{
    e.clearTable(ui->tab_employe);
    QString rech=ui->le_rech->text();
     ui->tab_employe->setModel(e.rechercher(rech));
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "volontaire.h"
#include <QMessageBox>
#include <QApplication>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(999999,999999, this));
    ui->tab_volontaire->setModel(V.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QDate datedenaissance=ui->le_date->date();
    QString email=ui->le_email->text();
    QString adresse=ui->le_adresse->text();
   Volontaire V(id,nom,prenom,datedenaissance,adresse,email);
   bool test=V.ajouter();

   if(test)
   {
    QMessageBox::information(nullptr, QObject::tr("OK"),
           QObject::tr("Ajout effectué\n"
                       "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_volontaire->setModel(V.afficher());
   }
   else
   {
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
            QObject::tr("Ajout effectué\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
   }
}


void MainWindow::on_pb_supprimer_clicked()
{
    Volontaire V1;
    V1.setid(ui->le_supprimer->text().toInt());
    bool test=V1.supprimer(V1.getid());
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("Supression avec succes");
        ui->tab_volontaire->setModel(V.afficher());

    }
     else
    {
        msgBox.setText("Echec de supression");
    }
}


void MainWindow::on_pb_modifier_clicked()
{
    int id=ui->le_id_2->text().toInt();
    QString NOM=ui->le_nom_2->text();
    QString PRENOM=ui->le_prenom_2->text();
    QDate datedenaissance=ui->le_date_2->date();
    QString adresse=ui->le_adresse_2->text();
    QString email=ui->le_email_2->text();

    Volontaire V1(id,NOM,PRENOM,datedenaissance,adresse,email);
    bool test=V1.update();

    if(test)
    {
     QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Modification effectué\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tab_volontaire->setModel(V.afficher());
    }
    else
    {
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
             QObject::tr("Modification erronée\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

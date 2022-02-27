#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"
#include<QMessageBox>
#include<QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0,9999,this));
    ui->tab_evenement->setModel(E.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toUInt();
    QString nom=ui->le_nom->text();
    QString type=ui->le_type->text();
    QString lieu=ui->le_lieu->text();
   // QString date_debut=ui->le_date_debut->text();
    //QString date_fin=ui->le_date_fin->text();


     Evenement E(id,nom,type,lieu/*,date_debut,date_fin*/);
     bool test=E.ajouter();
            if(test)
            {
             QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
             ui->tab_evenement->setModel(E.afficher());

            }
            else
            {
             QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                     QObject::tr("Ajout non effectué\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
            }
}

void MainWindow::on_le_supprimer_clicked()
{
Evenement E1; E1.setid(ui->le_id_supp->text().toInt()) ;
bool test=E1.supprimer(E1.getid());
QMessageBox msgBox;
if(test)
{
    msgBox.setText("Suppression  avec succes");
    ui->tab_evenement->setModel(E.afficher());
}
else
    msgBox.setText("Echec suppression");
msgBox.exec();
}

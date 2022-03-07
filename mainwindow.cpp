#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"
#include<QMessageBox>
#include<QIntValidator>
#include<QModelIndex>
#include <QRegExpValidator>
#include<QSqlQuery>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0,9999,this));
    ui->tab_evenement->setModel(E.afficher());
    QRegExp rxnom("\\b[a-zA-Z0-9]{2,10}\\b");
        QRegExpValidator *valinom =new QRegExpValidator(rxnom,this);
        ui->le_nom->setValidator(valinom);
        ui->le_nom_2->setValidator(valinom);
        ui->le_lieu->setValidator(valinom);
        ui->le_lieu_2->setValidator(valinom);
        QRegExp rxtype("\\b[a-zA-Z0-9]{2,10}\\b");
            QRegExpValidator *valitype =new QRegExpValidator(rxtype,this);
            ui->le_type->setValidator(valitype);
            ui->le_type_2->setValidator(valitype);
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
   QDate date_debut=ui->le_date_debut->date();
    QDate date_fin=ui->le_date_fin->date();


     Evenement E(id,nom,type,lieu,date_debut,date_fin);
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

void MainWindow::on_pb_modifier_clicked()
{
    int id=ui->le_id_2->text().toInt();
    QString nom=ui->le_nom_2->text();
    QString type=ui->le_type_2->text();
    QString lieu=ui->le_lieu_2->text();

    QDate date_debut=ui->le_date_debut_2->date();
    QDate date_fin=ui->le_date_fin_2->date();



    Evenement E(id,nom,type,lieu,date_debut,date_fin);
    bool test=E.modifierEvent(id);
       if(test)
       {
        QMessageBox::information(nullptr, QObject::tr("OK"),
               QObject::tr("Modification effectué\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_evenement->setModel(E.afficher());
       }
       else
       {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Modification non effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
       }
}



void MainWindow::on_pb_recherche_clicked()
{

     Evenement E ;
     QString rech =ui->recherche->text();
     if (rech=="")

         ui->tab_evenement->setModel(E.afficher());
     else
         ui->tab_evenement->setModel(E.recherche(rech));
}

void MainWindow::on_pb_triparnom_clicked()
{
    Evenement E ;
    ui->tab_evenement->setModel(E.trierevenement1());
}

void MainWindow::on_pb_triparid_clicked()
{
    Evenement E ;
    ui->tab_evenement->setModel(E.trierevenement2());
}

void MainWindow::on_tab_evenement_activated(const QModelIndex &index)
{
    QString val=ui->tab_evenement->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from evenement where id='"+val+"' or nom='"+val+"' or type='"+val+"' or lieu='"+val+"'  " );
    if(qry.exec())
    {
    while(qry.next())
    {
        ui->le_id_2->setText((qry.value(0).toString()));

        ui->le_nom_2->setText(qry.value(1).toString());
        ui->le_type_2->setText(qry.value(2).toString());
        ui->le_lieu_2->setText(qry.value(3).toString());
       // ui->le_date_debut_2->setDate(qry.value(4).toDate());
        //ui->le_date_fin_2->setDate(qry.value(5).toDate());

    }
    }
}

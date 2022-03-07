#include <QMessageBox>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "stock.h"
#include <QSqlQuery>
#include <QIntValidator>
#include <QSqlError>
#include<QSystemTrayIcon>
#include <QRegExp>
#include "connection.h"
MainWindow::MainWindow(QWidget *parent) : //Constructeur de la classe mainwindow généré automatiquement
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->le_id->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
    ui->la_qte->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
    ui->le_poids->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
    ui->la_taille->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
    ui->le_nom->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z]{7}")));
    ui->le_genre->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z]{6}")));

    ui->le_id_supp->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));

    ui->id_mod->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
    ui->qte_mod->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
    ui->poids_mod->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
    ui->taille_mod->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
    ui->nom_mod->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z]{7}")));
    ui->genre_mod->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z]{6}")));




    ui->le_id->setPlaceholderText("Entrez le id...");
    ui->le_nom->setPlaceholderText("Entrez le nom...");
    ui->le_genre->setPlaceholderText("Entrez le genre...");
    ui->la_qte->setPlaceholderText("Entrez la quantite...");
    ui->le_poids->setPlaceholderText("Entrez le poids...");
    ui->la_taille->setPlaceholderText("Entrez la taille...");

    ui->le_id_supp->setPlaceholderText("Entrez le id à supprimer...");

    ui->id_mod->setPlaceholderText("Entrez le id...");
    ui->nom_mod->setPlaceholderText("Entrez le nom...");
    ui->genre_mod->setPlaceholderText("Entrez le genre...");
    ui->qte_mod->setPlaceholderText("Entrez la quantite...");
    ui->poids_mod->setPlaceholderText("Entrez le poids...");
    ui->taille_mod->setPlaceholderText("Entrez la taille...");




    ui->tab_stock->setModel(S.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString id=ui->le_id->text();
    QString nom=ui->le_nom->text();
    QString genre=ui->le_genre->text();
    int quantite=ui->la_qte->text().toInt();
    int poids=ui->le_poids->text().toInt();
    int taille=ui->la_taille->text().toInt();
    QDate datep= ui->la_date->date();
    stock S(id,nom,quantite,poids,taille,genre,datep);
    bool test= S.ajouter();
    if(test)
    {
        //actualiser
        ui->tab_stock->setModel(S.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("Ajout effectué\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tri_alphabetique_stock_clicked()
{
    ui->tab_stock->setModel(S.afficher_tri_alphabetique_Stock());

}

void MainWindow::on_tri_desc_id_clicked()
{
    ui->tab_stock->setModel(S.afficher_tri_descendant_Stock());

}

void MainWindow::on_tri_asc_id_clicked()
{
ui->tab_stock->setModel(S.afficher_tri_identifiant_Stock());
}

void MainWindow::on_pb_supp_clicked()
{
    QSqlQuery query;

    S.setid(ui->le_id_supp->text());
    bool test=S.supprimer(S.getid());
     if(test)
    {
        ui->tab_stock->setModel(S.afficher());
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                //notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION STOCK ","La suppression du produit est effectuée",QSystemTrayIcon::Information,15000);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("supp effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                  QObject::tr("error::"), QMessageBox::Cancel);


}

void MainWindow::on_pb_modifier_clicked()
{
            S.setid(ui->id_mod->text());
            S.setnom(ui->nom_mod->text());
            S.setqte(ui->qte_mod->text().toInt());
            S.setdate(ui->date_mod->date());
            S.setgenre(ui->genre_mod->text());
            S.setpoids(ui->poids_mod->text().toInt());
            S.settaille(ui->taille_mod->text().toInt());





            if(S.modifier())
            {
                QMessageBox::information(nullptr, QObject::tr("modification produit"),
                                         QObject::tr("modification avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
                ui->tab_stock->setModel(S.afficher());
                ui->id_mod->clear();
                ui->nom_mod->clear();
                ui->qte_mod->clear();
                ui->poids_mod->clear();
                ui->taille_mod->clear();
                ui->date_mod->clear();
                ui->genre_mod->clear();




            }
            else
                QMessageBox::critical(nullptr, QObject::tr("modification produit"),
                                         QObject::tr("modification échouée.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_recherche_Stock_clicked()
{


    ui->tab_stock->setModel(S.recherche_nom(ui->input_rech->text()));



}

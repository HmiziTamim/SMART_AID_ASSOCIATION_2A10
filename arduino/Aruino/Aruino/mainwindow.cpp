#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_label()
{
    data=A.read_from_arduino();
QString idt=ui->idt->text();

    if(data=="1")

    ui->tabaff->setModel(C.afficher(idt));
    // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON


}

void MainWindow::on_verifier_clicked()   // implémentation du slot bouton on
{
     A.write_to_arduino("1"); //envoyer 1 à arduino
}
void MainWindow::on_pushButton_clicked()
{
    QString id=ui->id->text();
    QString nom=ui->nom->text();


    client C(id,nom);
    bool test= C.ajouter();
    if(test)
    {


        QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("Ajout effectué\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}


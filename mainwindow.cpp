#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patient.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditCINP->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEditAGEP->setValidator(new QIntValidator(0,999,this));
    ui->lineEditSUPP->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEditCINP_2->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEditAGEP_2->setValidator(new QIntValidator(0,999,this));
    QRegExp rxnom("\\b[a-zA-Z]{2,20}\\b");
        QRegExpValidator *valinom =new QRegExpValidator(rxnom,this);
        ui->lineEditNOMP->setValidator(valinom);
        ui->lineEditNOMP_2->setValidator(valinom);
        ui->lineEditPRENOMP->setValidator(valinom);
        ui->lineEditPRENOMP_2->setValidator(valinom);
    ui->tableView->setModel(P.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonQuitter_clicked()
{
    this->close();
}

void MainWindow::on_pushButtonAjouter_clicked()
{
    QString CINP=ui->lineEditCINP->text();
    QString NOMP=ui->lineEditNOMP->text();
    QString PRENOMP=ui->lineEditPRENOMP->text();
    QDate DATE_NAISSANCEP=ui->dateEdit->date();
    QString ADRESSEP=ui->lineEditADRESSEP->text();
    QString ETATP=ui->lineEditETATP->text();
    QString AGEP=ui->lineEditAGEP->text();
    Patient P(CINP,NOMP,PRENOMP,DATE_NAISSANCEP,ADRESSEP,ETATP,AGEP);
    bool test=P.ajouter();
    if(test)
        {

        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Ajout effectué\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(P.afficher());
        }
        else
    {
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"), QObject::tr("Ajout non effectué\n""Click Cancel to exit."), QMessageBox::Cancel);

    }
}


void MainWindow::on_pushButtonSUPP_clicked()
{
    Patient P1 ;
    P1.setCINP(ui->lineEditSUPP->text());
    bool test=P1.supprimer(P1.getCINP());
    if(test)
        {
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("suppression  effectué\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(P.afficher());
        }
        else
    {
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"), QObject::tr("suppression non effectué\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButtonModifier_clicked()
{
    QString CINP=ui->lineEditCINP_2->text();
    QString NOMP=ui->lineEditNOMP_2->text();
    QString PRENOMP=ui->lineEditPRENOMP_2->text();
    QDate DATE_NAISSANCEP=ui->dateEdit_2->date();
    QString ADRESSEP=ui->lineEditADRESSEP_2->text();
    QString ETATP=ui->lineEditETATP_2->text();
    QString AGEP=ui->lineEditAGEP_2->text();

    Patient P2(CINP,NOMP,PRENOMP,DATE_NAISSANCEP,ADRESSEP,ETATP,AGEP);
    bool test=P2.update();

    if(test)
    {
     QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Modification effectué\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tableView->setModel(P.afficher());
    }
    else
    {
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
             QObject::tr("Modification erronée\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

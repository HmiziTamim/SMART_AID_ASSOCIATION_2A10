#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>


using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduinoc = new arduino;
    arduinoc->openConnection();
    connect(arduinoc,&arduino::gotNewData,this,&MainWindow::updateGUI);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateGUI(QByteArray data)
{
    ui->lcdbyte->display(ui->lcdbyte->value() + data.size());

}





void MainWindow::on_on_clicked()
{
  if (arduinoc->isWritable())
      arduinoc->write("o");
  else
      qDebug() << "couldn't write ro serial:";


}

void MainWindow::on_off_clicked()
{
    if (arduinoc->isWritable())
        arduinoc->write("n");


    else
        qDebug() << "couldn't write ro serial:";




}

void MainWindow::on_verifier_clicked()
{

 QString idt=ui->idt->text();;

 QString id=ui->id->text();
 if (arduinoc->isWritable() && idt=="2A 2E C0 48")
      {  arduinoc->write("v");


     ui->tabaff->setModel(C.afficher(idt));

    }
    else
       { qDebug() << "couldn't write ro serial:";





    }





    //ui->tabaff->setModel(C.afficher(idt));}



    }

// select * base where id =="code carte.."



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


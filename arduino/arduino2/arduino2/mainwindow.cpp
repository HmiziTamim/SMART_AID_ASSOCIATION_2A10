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









void MainWindow::on_pushButton_clicked()
{
    if (arduinoc->isWritable())
       { arduinoc->write("v");


    QMessageBox::information(nullptr, QObject::tr("OK"),
                         QObject::tr("fonctionnement de  servo\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);}
    else
       { qDebug() << "couldn't write ro serial:";
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("non fonctionnement de  servo\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);}

}

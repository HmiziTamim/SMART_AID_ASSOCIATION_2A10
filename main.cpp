#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"



int main(int argc, char *argv[])
{
    /*QBarSet *set0 =new QBarSet("Altuve");
    QBarSet *set1 =new QBarSet("Martinez");
    QBarSet *set2 =new QBarSet("Segura");
    QBarSet *set3 =new QBarSet("Simmons");
    QBarSet *set4 =new QBarSet("Trout");

    *set0 << 283 << 341 << 313 << 338 << 346 << 335;
    *set1 << 250 << 315 << 282 << 307 << 303 << 330;
    *set2 << 294 << 246 << 257 << 319 << 300 << 325;
    *set3 << 248 << 244 << 265 << 281 << 278 << 313;
    *set4 << 323 << 287 << 299 << 315 << 306 << 313;*/



    QApplication a(argc, argv); //manages the GUI application's control flow and main settings
    Connection c;
    bool test=c.createconnect(); //etablir la cnx
    MainWindow w; //Appel du constructeur

    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}

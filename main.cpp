
#include "mainwindow.h"
#include "connection.h"
#include "evenement.h"
#include <QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QInputDialog>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator t;

    QStringList languages;
    Connection c;
    languages << "Frensh" << "English";
   const QString lang=QInputDialog::getItem(NULL,"Select language","languge",languages);
    if(lang == "English")
    {
        t.load(":/english.qm");

    }
    else if(lang != "Frensh")
    {
        a.installTranslator(&t);
    }

    bool test=c.createconnect();
      MainWindow w;
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

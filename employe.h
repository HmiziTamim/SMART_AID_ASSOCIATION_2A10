#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include <QSqlQueryModel>
#include <QDate>
#include "ui_mainwindow.h"
class Employe
{
public:
    Employe();
    Employe(QString,QString,QString,QString);
    Employe(QString,QString,QString,QString,QString,QString,QDate,QString,int,QString);
    QString getnom();
    QString getprenom();
    QString getcin();
    QString getnat();
    QString getetat();
    QString getemail();
    QDate getdate();
    QString getadresse();
    QString getsexe();
    int gettel();
    void setcin(QString);
    void setprenom(QString);
    void setnom(QString);
    void setnat(QString);
    void setetat(QString);
    void setemail(QString);
    void setdate(QDate);
    void setadresse(QString);
    void setsexe(QString);
    void settel(int);
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(QString);
    bool modifier(QString);
       QSqlQueryModel * triNom();
       QSqlQueryModel * tricin();
       QSqlQueryModel * triprenom();
       QSqlQueryModel * rechercher(QString rech);
       QSqlQueryModel * tritel();
       QSqlQueryModel * trinat();
       QSqlQueryModel * triadresse();
       QSqlQueryModel * triemail();
       void clearTable(QTableView *table);

        QSqlQueryModel* afficher(QString);
private:
    QString cin;
    int tel;
    QString nom,adresse,sexe;
    QString prenom,nat,etat,email;
    QDate naiss;
};

#endif // EMPLOYE_H

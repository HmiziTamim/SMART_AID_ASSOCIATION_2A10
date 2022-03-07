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
    Employe(int,QString,QString,QString);
    Employe(int,QString,QString,QString,QString,QString,QDate,QString,int,QString);
    QString getnom();
    QString getprenom();
    int getcin();
    QString getnat();
    QString getetat();
    QString getemail();
    QDate getdate();
    QString getadresse();
    QString getsexe();
    int gettel();
    void setcin(int);
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
    bool supprimer(int);
    bool modifier(int);
       QSqlQueryModel * triNom();
       QSqlQueryModel * tricin();
       QSqlQueryModel * triprenom();
       QSqlQueryModel * rechercher(QString rech);
       QSqlQueryModel * tritel();
       QSqlQueryModel * trinat();
       QSqlQueryModel * triadresse();
       QSqlQueryModel * triemail();
       void clearTable(QTableView *table);
private:
    int cin,tel;
    QString nom,adresse,sexe;
    QString prenom,nat,etat,email;
    QDate naiss;
};

#endif // EMPLOYE_H

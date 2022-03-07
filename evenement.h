#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include<QSqlQueryModel>
#include<QDate>

class Evenement
{
public:
    Evenement();
    Evenement(int,QString,QString,QString,QDate,QDate);
    int getid();
    QString getnom();
    QString gettype();
    QString getlieu();
    QDate getdate_debut();
    QDate getdate_fin();
    void setid(int);
    void setnom(QString);
    void settype(QString);
    void setlieu(QString);
    void setdate_debut(QDate);
    void setdate_fin(QDate);
    bool ajouter();
    QSqlQueryModel* afficher ();
    bool supprimer (int);
    bool modifierEvent(int);
    QSqlQueryModel* recherche(QString nom);
    QSqlQueryModel * trierevenement1();
    QSqlQueryModel * trierevenement2();
private:
    int id;
    QString nom,type,lieu;
QDate date_debut,date_fin;
};

#endif // EVENEMENT_H

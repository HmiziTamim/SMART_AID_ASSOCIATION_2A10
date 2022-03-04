#ifndef VOLONTAIRE_H
#define VOLONTAIRE_H

#include <QString>
#include <QSqlQueryModel>
#include<QDateEdit>
#include<QDate>


class Volontaire
{
public:
    Volontaire();
    Volontaire(int,QString,QString,QDate,QString, QString);
    int getid();
    QString getnom();
    QString getprenom();
    QDate getdatedenaissance();
    QString getadresse();
    QString getemail();

    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setdatedenaissance(QDate);
    void setadresse(QString);
    void setemail(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool update();
private:
    int id;
    QString nom,prenom;
    QDate datedenaissance;
    QString adresse;
    QString email;
};

#endif // VOLONTAIRE_H

#ifndef VOLONTAIRE_H
#define VOLONTAIRE_H

#include <QString>
#include <QSqlQueryModel>
#include<QDateEdit>
#include<QDate>
#include<QTableView>

class Volontaire
{
public:
    Volontaire();
    Volontaire(QString,QString,QString,QDate,QString, QString ,QString,QString);
    QString getid();
    QString getnom();
    QString getprenom();
    QDate getdatedenaissance();
    QString getadresse();
    QString getemail();
    QString getdispo();
    QString getnum();


    void setid(QString);
    void setnom(QString);
    void setprenom(QString);
    void setdatedenaissance(QDate);
    void setadresse(QString);
    void setemail(QString);
    void setdispo(QString);
    void setnum(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool update();

    QStringList lister();
    QStringList listerEmail();
    void recup(QString id,QString &nom,QString &prenom,QDate &datedenaissance,QString &adresse, QString &email,QString &dispo,QString &num);

    QSqlQueryModel *rechercher(QString);

    QSqlQueryModel *triNom();
    QSqlQueryModel *triprenom();
    QSqlQueryModel *tridatedenaissance();

    void clearTable(QTableView *table);
private:
    QString id;
    QString nom,prenom;
    QDate datedenaissance;
    QString adresse;
    QString email;
    QString dispo;
    QString num;
};

#endif // VOLONTAIRE_H

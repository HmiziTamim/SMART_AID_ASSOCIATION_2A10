#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include<QSqlQueryModel>
class Evenement
{
public:
    Evenement();
    Evenement(int,QString,QString,QString/*,QString,QString*/);
    int getid();
    QString getnom();
    QString gettype();
    QString getlieu();
    QString getdate_debut();
    QString getdate_fin();
    void setid(int);
    void setnom(QString);
    void settype(QString);
    void setlieu(QString);
    void setdate_debut(QString);
    void setdate_fin(QString);
    bool ajouter();
    QSqlQueryModel* afficher ();
    bool supprimer (int);
private:
    int id;
    QString nom,type,lieu/*,date_debut,date_fin*/;

};

#endif // EVENEMENT_H

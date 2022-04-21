#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QString>
#include<QDate>
#include<QSqlQuery>  //executing and manipulating SQL statements
#include <QSqlQueryModel>

class historique
{
public:
    historique();
    historique(QString,QString);

        void setEtat(QString);
        void setidh(QString);




        void ajouter_historique();
        QSqlQueryModel * afficherHistorique();

    private:
        QString etat;
        QDateTime date;

        QString idh;

};
#endif // HISTORIQUE_H

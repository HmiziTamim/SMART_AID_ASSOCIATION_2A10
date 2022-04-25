#include "historique.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>
#include <QDateTime>

     historique::historique()
    {
        date=QDateTime::currentDateTime();

    }
    historique:: historique(QString etat,QString idh)
    {

        date=QDateTime::currentDateTime();
        this->etat=etat;
        this->idh=idh;


    }


    void historique::ajouter_historique()
    {


        QSqlQuery query;
        query.prepare("INSERT INTO HISTORIQUE (etat,idh,date_historique) VALUES(:etat,:idh,:DATE_HISTORIQUE ) ");
        query.bindValue(":etat",etat);
        query.bindValue(":DATE_HISTORIQUE",date);
        query.bindValue(":idh", idh);


        query.exec();











    }
    void historique::setEtat(QString etat)
    {
        this->etat=etat;
    }

    void historique::setidh(QString idh){this->idh=idh;}


    QSqlQueryModel * historique::afficherHistorique()
    {
        QSqlQueryModel * model= new QSqlQueryModel();


            model->setQuery("select etat,idh,date_historique FROM HISTORIQUE;");



        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ETAT"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("Date current"));

        return model;
}





#include "histosupp.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>

histosupp::histosupp(){
    idhs="";

}

histosupp::histosupp(QString idhs)
{
    this->idhs=idhs;


}

QString histosupp::getidhs(){return idhs;}

void histosupp::setidhs(QString idhs){this->idhs=idhs;}


bool histosupp :: ajoutSupp()
{

    QSqlQuery query;

    //Prendra la requête en paramètre pour la préparer à l’exécution.
    query.prepare("insert into histosupp (idhs)" "values (:idhs)");

    //bindValue+requete
    query.bindValue(":idhs", idhs);




    return  query.exec();
}
QSqlQueryModel * histosupp :: affichSupp()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM histosupp");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));


    return model;
}







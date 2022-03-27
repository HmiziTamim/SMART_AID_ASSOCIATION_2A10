#include "histomod.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>
histomod::histomod()
{
    idh="";
    quantiteh=0;
    poidsh=0;
    tailleh=0;
    nomh="";
    genreh="";
   dateph.toString("yyyy/dd/mm");
}

histomod::histomod(QString idh,QString nomh,int quantiteh,int poidsh,int tailleh,QString genreh,QDate dateph)
{
    this->idh=idh;
    this->nomh=nomh;
    this->quantiteh=quantiteh;
    this->dateph=dateph;
    this->genreh=genreh;
    this->poidsh=poidsh;
    this->tailleh=tailleh;

}

QString histomod::getidh(){return idh;}
QString histomod::getnomh(){return nomh;}
int histomod::getqteh(){return quantiteh;}
QDate histomod::getdateh(){return dateph;}
QString histomod::getgenreh(){return genreh;}
int histomod::getpoidsh(){return poidsh;}
int histomod::gettailleh(){return tailleh;}
void histomod::setidh(QString idh){this->idh=idh;}
void histomod::setnomh(QString nomh){this->nomh=nomh;}
void histomod::setqteh(int quantiteh){this->quantiteh=quantiteh;}
void histomod::setdateh(QDate dateph){this->dateph=dateph;}
void histomod::setgenreh(QString genreh){this->genreh=genreh;}
void histomod::setpoidsh(int poidsh){this->poidsh=poidsh;}
void histomod::settailleh(int tailleh){this->tailleh=tailleh;}




bool histomod::ajouter()
{
QString quantite_string = QString::number(quantiteh);
QString poids_string = QString::number(poidsh);
QString taille_string = QString::number(tailleh);
QSqlQuery query;

//Prendra la requête en paramètre pour la préparer à l’exécution.
query.prepare("insert into histomod (idh,nomh,quantiteh,poidsh,tailleh,genreh,dateph)" "values (:idh,:nomh,:quantiteh,:poidsh,:tailleh,:genreh,:dateph)");

//bindValue+requete
query.bindValue(":idh", idh);
query.bindValue(":nomh", nomh );
query.bindValue(":quantiteh", quantite_string );
query.bindValue(":dateph", dateph );
query.bindValue(":poidsh", poids_string );
query.bindValue(":tailleh", taille_string );
query.bindValue(":genreh", genreh );




return  query.exec();

}

QSqlQueryModel* histomod::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("SELECT * FROM histomod");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Taille"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Genre"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));


return model;
}

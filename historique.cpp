#include "historique.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>
historique::historique()
{
    idh="";
    quantiteh=0;
    poidsh=0;
    tailleh=0;
    nomh="";
    genreh="";
   dateph.toString("yyyy/dd/mm");
}

historique::historique(QString idh,QString nomh,int quantiteh,int poidsh,int tailleh,QString genreh,QDate dateph)
{
    this->idh=idh;
    this->nomh=nomh;
    this->quantiteh=quantiteh;
    this->dateph=dateph;
    this->genreh=genreh;
    this->poidsh=poidsh;
    this->tailleh=tailleh;

}

QString historique::getidh(){return idh;}
QString historique::getnomh(){return nomh;}
int historique::getqteh(){return quantiteh;}
QDate historique::getdateh(){return dateph;}
QString historique::getgenreh(){return genreh;}
int historique::getpoidsh(){return poidsh;}
int historique::gettailleh(){return tailleh;}
void historique::setidh(QString idh){this->idh=idh;}
void historique::setnomh(QString nomh){this->nomh=nomh;}
void historique::setqteh(int quantiteh){this->quantiteh=quantiteh;}
void historique::setdateh(QDate dateph){this->dateph=dateph;}
void historique::setgenreh(QString genreh){this->genreh=genreh;}
void historique::setpoidsh(int poidsh){this->poidsh=poidsh;}
void historique::settailleh(int tailleh){this->tailleh=tailleh;}




bool historique::ajouter()
{
QString quantite_string = QString::number(quantiteh);
QString poids_string = QString::number(poidsh);
QString taille_string = QString::number(tailleh);
QSqlQuery query;

//Prendra la requête en paramètre pour la préparer à l’exécution.
query.prepare("insert into historique (idh,nomh,quantiteh,poidsh,tailleh,genreh,dateph)" "values (:idh,:nomh,:quantiteh,:poidsh,:tailleh,:genreh,:dateph)");

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

QSqlQueryModel* historique::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("SELECT * FROM historique");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Taille"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Genre"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));


return model;
}
/*bool historique::modifier(){
    QSqlQuery query;
    QString quantite_string = QString::number(quantiteh);
    QString poids_string = QString::number(poidsh);
    QString taille_string = QString::number(tailleh);
    query.prepare("UPDATE historique set idh=:idh,nomh=:nomh,quantiteh=:quantiteh,poidsh=:poidsh,tailleh=:tailleh,genreh=:genreh,dateph=:dateph WHERE idh=:idh");

    query.bindValue(":idh", idh);
    query.bindValue(":nomh", nomh );
    query.bindValue(":quantiteh", quantite_string );
    query.bindValue(":dateph", dateph );
    query.bindValue(":poidsh", poids_string );
    query.bindValue(":tailleh", taille_string );
    query.bindValue(":genreh", genreh );



    return (query.exec());
}*/


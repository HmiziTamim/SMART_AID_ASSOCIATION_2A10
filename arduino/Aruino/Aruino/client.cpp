#include "client.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>
client::client()
{
    id="";
    nom="";


}

client::client(QString id,QString nom)
{

    this->id=id;
    this->nom=nom;


}

QString client::getid(){return id;}
QString client::getnom(){return nom;}

void client::setid(QString id){this->id=id;}
void client::setnom(QString nom){this->nom=nom;}




bool client::ajouter()
{

QSqlQuery query;

//Prendra la requête en paramètre pour la préparer à l’exécution.
query.prepare("insert into client (id,nom)" "values (:id,:nom)");

//bindValue+requete
query.bindValue(":id", id);
query.bindValue(":nom", nom );


return  query.exec();

}

QSqlQueryModel* client::afficher(QString idt)
{
QSqlQueryModel * model=new QSqlQueryModel();


model->setQuery("SELECT * FROM client WHERE id LIKE '"+idt+"'");


model->setHeaderData(0, Qt::Horizontal, QObject::tr("id client"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));


return model;
}

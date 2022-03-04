#include "volontaire.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include<QDate>

Volontaire::Volontaire()
{
id=0; nom="";prenom="";email="";adresse="";

}

Volontaire::Volontaire(int id,QString nom,QString prenom,QDate datedenaissance,QString adresse,QString email)
{
this->id=id;this->nom=nom;this->prenom=prenom;
this->datedenaissance=datedenaissance;
this->adresse=adresse;
this->email=email;
}

int Volontaire::getid(){return id;}
QString Volontaire::getnom(){return nom;}
QString Volontaire::getprenom(){return prenom;}
QDate Volontaire::getdatedenaissance(){return datedenaissance;}
QString Volontaire::getadresse(){return adresse;}
QString Volontaire::getemail(){return email;}


void Volontaire::setid(int id){this->id=id;}
void Volontaire::setnom(QString nom){this->nom=nom;}
void Volontaire::setprenom(QString prenom){this->prenom=prenom;}
void Volontaire::setdatedenaissance(QDate datedenaissance){this->datedenaissance=datedenaissance;}
void Volontaire::setadresse(QString adresse){this->adresse=adresse;}
void Volontaire::setemail(QString email){this->email=email;}

bool Volontaire::ajouter()
{
    QSqlQuery query;
   QString id_string=QString::number(id);
          query.prepare("INSERT INTO Volontaire (id, nom, prenom, datedenaissance, adresse, email) " "VALUES (:id, :forename, :surname, :datedenaissance, :adresse, :email)");
          query.bindValue(0, id_string);
          query.bindValue(1, nom);
          query.bindValue(2,prenom);
          query.bindValue(3,datedenaissance);
          query.bindValue(4,adresse);
          query.bindValue(5,email);
          return query.exec();
}


bool Volontaire::supprimer(int id)
{
    QSqlQuery query;
   QString id_string=QString::number(id);
          query.prepare("Delete from Volontaire where id=:id");
          query.bindValue(0,id);
          return query.exec();
}


QSqlQueryModel* Volontaire::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM Volontaire");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
    return model;
}

bool Volontaire::update()
{
    QSqlQuery  query;
query.prepare("UPDATE Volontaire SET id=:id ,nom=:NOM, prenom=:PRENOM, datedenaissance=:DATEDENAISSANCE, adresse=:ADRESSE, email=:EMAIL   where id=:id");
query.bindValue(":id",id);
query.bindValue(":NOM",nom);
query.bindValue(":PRENOM",prenom);
query.bindValue(":DATEDENAISSANCE",datedenaissance);
query.bindValue(":ADRESSE",adresse);
query.bindValue(":EMAIL",email);

return query.exec();
}

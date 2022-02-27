#include "evenement.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Evenement::Evenement()
{
id=0;
nom="";
type="";
lieu="";
//date_debut="";
//date_fin="";
}
Evenement::Evenement(int id,QString nom,QString type,QString lieu/*,QString date_debut,QString date_fin*/)
{this->id=id;this->nom=nom;this->type=type;this->lieu=lieu;/*this->date_debut=date_debut;this->date_fin=date_fin;*/ }
int Evenement::getid(){return id;}
QString Evenement:: getnom(){return nom;}
QString Evenement:: gettype(){return type;}
QString Evenement:: getlieu(){return lieu;}
//QString Evenement:: getdate_debut(){return date_debut;}
//QString Evenement:: getdate_fin(){return date_fin;}
void Evenement:: setid(int id){this->id=id;}
void Evenement:: setnom(QString nom){this->nom=nom;}
void Evenement:: settype(QString type){this->type=type;}
void Evenement:: setlieu(QString lieu){this->lieu=lieu;}
//void Evenement:: setdate_debut(QString date_debut){this->date_debut=date_debut;}
//void Evenement:: setdate_fin(QString date_fin){this->date_fin=date_fin;}
bool Evenement:: ajouter()
{
QSqlQuery query;
QString id_string=QString::number(id);
      query.prepare("INSERT INTO EVENEMENT (id,nom,type,lieu) "
                    "VALUES (:id, :nom,:type,:lieu)");
      query.bindValue(":id",id_string );
      query.bindValue(":nom",nom);
     // query.bindValue(":date_debut",date_debut);
      //query.bindValue(":date_fin",date_fin);
      query.bindValue(":type",type);
      query.bindValue(":lieu",lieu);
      return query.exec();




}
bool Evenement::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from evenement where id=:id");
    query.bindValue(0,id);

    return query.exec();


}

QSqlQueryModel* Evenement::afficher()
{
 QSqlQueryModel* model=new QSqlQueryModel();
       model->setQuery("SELECT * FROM evenement ");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant "));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("lieu"));

return model;
}




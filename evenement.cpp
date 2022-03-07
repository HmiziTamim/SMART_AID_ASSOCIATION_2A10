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
Evenement::Evenement(int id,QString nom,QString type,QString lieu,QDate date_debut,QDate date_fin)
{this->id=id;this->nom=nom;this->type=type;this->lieu=lieu;this->date_debut=date_debut;this->date_fin=date_fin; }
int Evenement::getid(){return id;}
QString Evenement:: getnom(){return nom;}
QString Evenement:: gettype(){return type;}
QString Evenement:: getlieu(){return lieu;}
QDate Evenement:: getdate_debut(){return date_debut;}
QDate Evenement:: getdate_fin(){return date_fin;}
void Evenement:: setid(int id){this->id=id;}
void Evenement:: setnom(QString nom){this->nom=nom;}
void Evenement:: settype(QString type){this->type=type;}
void Evenement:: setlieu(QString lieu){this->lieu=lieu;}
void Evenement:: setdate_debut(QDate date_debut){this->date_debut=date_debut;}
void Evenement:: setdate_fin(QDate date_fin){this->date_fin=date_fin;}
bool Evenement:: ajouter()
{
QSqlQuery query;
QString id_string=QString::number(id);
      query.prepare("INSERT INTO EVENEMENT (id,nom,type,lieu,date_debut,date_fin) "
                    "VALUES (:id, :nom,:type,:lieu,:date_debut,:date_fin)");
      query.bindValue(":id",id_string );
      query.bindValue(":nom",nom);
      query.bindValue(":date_debut",date_debut);
      query.bindValue(":date_fin",date_fin);
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
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_debut"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_fin"));

return model;
}


bool Evenement::modifierEvent(int id)

{
    QSqlQuery query;

    query.prepare("update evenement set nom=:nom, type=:type, lieu=:lieu, date_debut=:date_debut,date_fin=:date_fin where id=:id");
    query.bindValue(":id",id );
    query.bindValue(":nom",nom);
    query.bindValue(":type",type);
    query.bindValue(":lieu",lieu);
    query.bindValue(":date_debut",date_debut);
    query.bindValue(":date_fin",date_fin);
    return query.exec();

}

QSqlQueryModel* Evenement::recherche(QString nom)

 {

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from evenement WHERE(nom  LIKE '%"+nom+"%')");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("lieu"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_debut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_fin"));
    return  model ;

}

QSqlQueryModel *Evenement::trierevenement1()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from evenement order by nom") ;
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("lieu"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_debut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_fin"));


    return  model ;

}

QSqlQueryModel *Evenement::trierevenement2()
{
    QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery("select * from evenement order by id ") ;
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("lieu"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_debut"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_fin"));
 return  model ;
}

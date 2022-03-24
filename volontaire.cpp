#include "volontaire.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include<QDate>
#include <QTableView>

Volontaire::Volontaire()
{
id=""; nom="";prenom="";email="";adresse="";num="";

}

Volontaire::Volontaire(QString id,QString nom,QString prenom,QDate datedenaissance,QString adresse,QString email,QString dispo,QString num)
{
this->id=id;this->nom=nom;this->prenom=prenom;
this->datedenaissance=datedenaissance;
this->adresse=adresse;
this->email=email;
this->dispo=dispo;
this->num=num;
}

QString Volontaire::getid(){return id;}
QString Volontaire::getnom(){return nom;}
QString Volontaire::getprenom(){return prenom;}
QDate Volontaire::getdatedenaissance(){return datedenaissance;}
QString Volontaire::getadresse(){return adresse;}
QString Volontaire::getemail(){return email;}
QString Volontaire::getdispo(){return dispo;}
QString Volontaire::getnum(){return num;}


void Volontaire::setid(QString id){this->id=id;}
void Volontaire::setnom(QString nom){this->nom=nom;}
void Volontaire::setprenom(QString prenom){this->prenom=prenom;}
void Volontaire::setdatedenaissance(QDate datedenaissance){this->datedenaissance=datedenaissance;}
void Volontaire::setadresse(QString adresse){this->adresse=adresse;}
void Volontaire::setemail(QString email){this->email=email;}
void Volontaire::setdispo(QString dispo){this->dispo=dispo;}
void Volontaire::setnum(QString num){this->num=num;}


QStringList Volontaire::lister(){
QSqlQuery q;
q.prepare("select id from Volontaire");
q.exec();
QStringList l;
while(q.next()){
l<<q.value(0).toString();
}
return l;
}

QStringList Volontaire::listerEmail(){
QSqlQuery a;
a.prepare("select email from Volontaire");
a.exec();
QStringList b;
while(a.next()){
b<<a.value(0).toString();
}
return b;
}


bool Volontaire::ajouter()
{
    QSqlQuery query;
          query.prepare("INSERT INTO Volontaire (id, nom, prenom, datedenaissance, adresse, email ,dispo, num) " "VALUES (:id, :forename, :surname, :datedenaissance, :adresse, :email, :dispo, :num)");
          query.bindValue(0, id);
          query.bindValue(1, nom);
          query.bindValue(2,prenom);
          query.bindValue(3,datedenaissance);
          query.bindValue(4,adresse);
          query.bindValue(5,email);
          query.bindValue(6,dispo);
          query.bindValue(7,num);
          return query.exec();
}


bool Volontaire::supprimer(QString id)
{
    QSqlQuery query;
   //QString id_string=QString::number(id);
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
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Dispo"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num"));
    return model;
}

bool Volontaire::update()
{

    QSqlQuery  query;

query.prepare("UPDATE Volontaire SET id=:id ,nom=:NOM, prenom=:PRENOM, datedenaissance=:DATEDENAISSANCE, adresse=:ADRESSE, email=:EMAIL ,dispo=:dispo ,num=:num   where id=:id");
query.bindValue(":id",id);
query.bindValue(":NOM",nom);
query.bindValue(":PRENOM",prenom);
query.bindValue(":DATEDENAISSANCE",datedenaissance);
query.bindValue(":ADRESSE",adresse);
query.bindValue(":EMAIL",email);
query.bindValue(":dispo",dispo);
query.bindValue(":num",num);

return query.exec();
}


void Volontaire::recup(QString id,QString &nom,QString &prenom,QDate &datedenaissance,QString &adresse, QString &email,QString &dispo,QString &num)
{

   QSqlQuery  query;

query.prepare("SELECT * FROM Volontaire where id=:id");
query.bindValue(":id",id);
query.exec();
query.next();
prenom=query.value(1).toString();
nom=query.value(2).toString();
datedenaissance=query.value(3).toDate();
adresse=query.value(4).toString();
email=query.value(5).toString();
dispo=query.value(6).toString();
num=query.value(7).toString();
}




void Volontaire::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}


QSqlQueryModel *Volontaire::rechercher(QString rech)
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from Volontaire where id like '"+rech+"%' or prenom like '"+rech+"%'  or nom like '"+rech+"%' or adresse like '"+rech+"%' or email like '"+rech+"%' or dispo like '"+rech+"%' or num like '"+rech+"%' ;");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Dispo"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num"));
return model;
}

// TRI
QSqlQueryModel* Volontaire::triNom()
 {
     QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("SELECT * FROM Volontaire ORDER BY nom");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("Dispo"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num"));
            return model;
 }

QSqlQueryModel* Volontaire::triprenom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
           model->setQuery("SELECT * FROM Volontaire ORDER BY prenom");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
           model->setHeaderData(6, Qt::Horizontal, QObject::tr("Dispo"));
           model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num"));
           return model;
}
QSqlQueryModel* Volontaire::tridatedenaissance()
{
    QSqlQueryModel * model= new QSqlQueryModel();
           model->setQuery("SELECT * FROM Volontaire ORDER BY datedenaissance");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr("Email"));
           model->setHeaderData(6, Qt::Horizontal, QObject::tr("Dispo"));
           model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num"));
           return model;
}

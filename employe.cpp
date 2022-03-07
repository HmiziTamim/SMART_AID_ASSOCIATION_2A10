#include "employe.h"
#include<QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QPixmap>
#include <QObject>
#include <QDate>
#include <QMessageBox>
Employe::Employe()
{
cin=0;
nom="";
prenom="";
nat="";
etat="";
email="";
tel=0;
adresse="";

}
Employe::Employe(int cin,QString nom,QString prenom,QString nat,QString etat,QString email,QDate naiss,QString adresse,int tel,QString sexe)
{this->cin=cin;this->nom=nom;this->prenom=prenom;this->nat=nat;this->etat=etat;this->email=email;this->naiss=naiss;this->adresse=adresse;this->tel=tel;this->sexe=sexe;}
QString Employe::getnom(){return nom;}
QString Employe::getprenom(){return prenom;}
QString Employe::getnat(){return nat;}
QString Employe::getetat(){return etat;}
QString Employe::getemail(){return email;}
QString Employe::getsexe(){return sexe;}
int Employe::getcin(){return cin;}
QDate Employe::getdate(){return naiss;}
QString Employe::getadresse(){return adresse;}
int Employe::gettel(){return tel;}

void Employe::setcin(int cin){this->cin=cin;}
void Employe::setprenom(QString prenom){this->prenom=prenom;}
void Employe::setnom(QString nom){this->nom=nom;}
void Employe::setnat(QString nat){this->nat=nat;}
void Employe::setetat(QString etat){this->etat=etat;}
void Employe::setemail(QString email){this->email=email;}
void Employe::setdate(QDate naiss){this->naiss=naiss;}
void Employe::setadresse(QString adresse){this->adresse=adresse;}
void Employe::settel(int tel){this->tel=tel;}
void Employe::setsexe(QString sexe){this->sexe=sexe;}
bool Employe::ajouter()
{


    QSqlQuery query;
    QString cin_string=QString::number(cin);
    QString tel_string=QString::number(tel);
          query.prepare("INSERT INTO employe (cin, nom, prenom,nat,etat,email,naiss,adresse,tel,sexe) "
                        "VALUES (:cin, :nom, :prenom, :nat, :etat, :email, :naiss, :adresse, :tel, :sexe)");
          query.bindValue(":cin", cin_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":nat", nat);
          query.bindValue(":etat", etat);
          query.bindValue(":email", email);
           query.bindValue(":naiss", naiss);
           query.bindValue(":adresse", adresse);
           query.bindValue(":tel", tel_string);
           query.bindValue(":sexe", sexe);
         return query.exec();


}
bool Employe::supprimer(int cin)
{
    QSqlQuery query;
      query.prepare("Delete from  employe where cin=:cin");
          query.bindValue(0, cin);
          return query.exec();


}
QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM employe");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nationnalité"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Etat"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de naissance"));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("Adresse"));
          model->setHeaderData(8, Qt::Horizontal, QObject::tr("Telephone"));
          model->setHeaderData(9, Qt::Horizontal, QObject::tr("Sexe"));
    return model;
}
bool Employe::modifier(int cin)
{  QSqlQuery query;
    query.prepare("update employe set nom=:nom,prenom=:prenom,nat=:nat,etat=:etat,email=:email,naiss=:naiss,adresse=:adresse,tel=:tel,sexe=:sexe where cin=:cin");
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":nat",nat);
     query.bindValue(":etat",etat);
      query.bindValue(":email",email);
   query.bindValue(":naiss",naiss);
   query.bindValue(":adresse",adresse);
   query.bindValue(":tel",tel);
    query.bindValue(":sexe",sexe);
    return query.exec();


}

QSqlQueryModel* Employe::triNom()
 {
     QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("SELECT * FROM employe ORDER BY NOM");
            return model;
 }
QSqlQueryModel* Employe::tricin()
{
    QSqlQueryModel * model= new QSqlQueryModel();
           model->setQuery("SELECT * FROM employe ORDER BY CIN");
           return model;
}
QSqlQueryModel* Employe::triprenom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
           model->setQuery("SELECT * FROM employe ORDER BY PRENOM");
           return model;
}
QSqlQueryModel* Employe::trinat()
{
    QSqlQueryModel * model= new QSqlQueryModel();
           model->setQuery("SELECT * FROM employe ORDER BY NAT");
           return model;
}
QSqlQueryModel* Employe::tritel()
{
    QSqlQueryModel * model= new QSqlQueryModel();
           model->setQuery("SELECT * FROM employe ORDER BY TEL");
           return model;
}
QSqlQueryModel* Employe::triadresse()
{
    QSqlQueryModel * model= new QSqlQueryModel();
           model->setQuery("SELECT * FROM employe ORDER BY ADRESSE");
           return model;
}
QSqlQueryModel* Employe::triemail()
{
    QSqlQueryModel * model= new QSqlQueryModel();
           model->setQuery("SELECT * FROM employe ORDER BY EMAIL");
           return model;
}
QSqlQueryModel* Employe::rechercher(QString rech)
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from employe where cin like '"+rech+"%' or prenom like '"+rech+"%'  or nom like '"+rech+"%' or adresse like '"+rech+"%' or email like '"+rech+"%' or nat like '"+rech+"%' or etat like '"+rech+"%' ;");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nationnalité"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Etat"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de naissance"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("Adresse"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("Telephone"));
model->setHeaderData(9, Qt::Horizontal, QObject::tr("Sexe"));
return model;
return model;
}
void Employe::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}


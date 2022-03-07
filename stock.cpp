#include "stock.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
stock::stock()
{
    id="";
    quantite=0;
    poids=0;
    taille=0;
    nom="";
    genre="";
   datep.toString("yyyy/dd/mm");
}
stock::stock(QString id,QString nom,int quantite,int poids,int taille,QString genre,QDate datep)
{
    this->id=id;
    this->nom=nom;
    this->quantite=quantite;
    this->datep=datep;
    this->genre=genre;
    this->poids=poids;
    this->taille=taille;

}
QString stock::getid(){return id;}
QString stock::getnom(){return nom;}
int stock::getqte(){return quantite;}
QDate stock::getdate(){return datep;}
QString stock::getgenre(){return genre;}
int stock::getpoids(){return poids;}
int stock::gettaille(){return taille;}
void stock::setid(QString id){this->id=id;}
void stock::setnom(QString nom){this->nom=nom;}
void stock::setqte(int quantite){this->quantite=quantite;}
void stock::setdate(QDate datep){this->datep=datep;}
void stock::setgenre(QString genre){this->genre=genre;}
void stock::setpoids(int poids){this->poids=poids;}
void stock::settaille(int taille){this->taille=taille;}


bool stock::ajouter()
{
QString quantite_string = QString::number(quantite);
QString poids_string = QString::number(poids);
QString taille_string = QString::number(taille);
QSqlQuery query;

//Prendra la requête en paramètre pour la préparer à l’exécution.
query.prepare("insert into STOCK (id,nom,quantite,poids,taille,genre,datep)" "values (:id,:nom,:quantite,:poids,:taille,:genre,:datep)");
//bindValue+requete
query.bindValue(":id", id);
query.bindValue(":nom", nom );
query.bindValue(":quantite", quantite_string );
query.bindValue(":datep", datep );
query.bindValue(":poids", poids_string );
query.bindValue(":taille", taille_string );
query.bindValue(":genre", genre );




return  query.exec();

}

QSqlQueryModel* stock::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("SELECT * FROM stock");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Taille"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Genre"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));


return model;
}
bool stock::modifier(){
    QSqlQuery query;
    QString quantite_string = QString::number(quantite);
    QString poids_string = QString::number(poids);
    QString taille_string = QString::number(taille);
    query.prepare("UPDATE stock set id=:id,nom=:nom,quantite=:quantite,poids=:poids,taille=:taille,genre=:genre,datep=:datep WHERE id=:id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom );
    query.bindValue(":quantite", quantite_string );
    query.bindValue(":datep", datep );
    query.bindValue(":poids", poids_string );
    query.bindValue(":taille", taille_string );
    query.bindValue(":genre", genre );


    return (query.exec());
}


bool stock::supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("Delete from stock where id=:id");

    query.bindValue(0, id);

    return query.exec();



}


QSqlQueryModel * stock::afficher_tri_alphabetique_Stock(){

    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM stock ORDER BY nom");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Taille"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));
    return model;


}
QSqlQueryModel * stock::afficher_tri_identifiant_Stock(){

    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from stock ORDER BY id");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Taille"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));
    return model;
}



QSqlQueryModel * stock::afficher_tri_descendant_Stock(){

    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from stock ORDER BY id DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Taille"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));
    return model;
}


QSqlQueryModel * stock::recherche_nom(QString nom)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from stock WHERE nom LIKE '%"+nom+"%'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Taille"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date"));
    return model;
}
/*QSqlQueryModel *   stock::recherche_date(QString datep)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from stock WHERE datep LIKE  "+datep+"");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Couleur"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Taille"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date"));
    return model;
}
*/


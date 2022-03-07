#ifndef STOCK_H
#define STOCK_H
#include <QString>
#include<QDate>
#include<QSqlQuery>
#include <QSqlQueryModel>

class stock
{

public:
    //constructeurs
    stock();
    stock(QString,QString,int,int,int,QString,QDate);



    //getters
    QString getid();//accées lecture//récupérer la valeur d'un attribut
    QString getnom();
    int getqte();
    QDate getdate();
    QString getgenre();
    int getpoids();
    int gettaille();

    //setters
    void setid(QString);
    void setnom(QString);
    void setqte(int);
    void setdate(QDate);//demande changement d'etats//modifier un attribut
    void setgenre(QString);
    void setpoids(int);
    void settaille(int);


    //méthodes
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier();


    //métiers
    QSqlQueryModel * afficher_tri_alphabetique_Stock();
    QSqlQueryModel * afficher_tri_identifiant_Stock();
    QSqlQueryModel * afficher_tri_descendant_Stock();
    QSqlQueryModel * recherche_nom(QString);


private:
    int quantite,poids,taille;
    QString nom,genre,id;
    QDate datep;
};

#endif // STOCK_H

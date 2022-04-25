#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include<QDate>
#include<QSqlQuery>
#include <QSqlQueryModel>

class client
{

public:
    //constructeurs
    client();
    client(QString,QString);



    //getters

    QString getid();//accées lecture//récupérer la valeur d'un attribut
    QString getnom();





    //setters
    void setid(QString);
    void setnom(QString);



    //méthodes
    bool ajouter();
    QSqlQueryModel * afficher(QString);
    bool supprimer(QString);
    bool modifier();




private:

    QString nom,id;

};




#endif // CLIENT_H

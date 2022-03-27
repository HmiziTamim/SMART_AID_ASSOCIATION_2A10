#ifndef HISTOSUPP_H
#define HISTOSUPP_H
#include <QString>
#include<QDate>
#include<QSqlQuery>
#include <QSqlQueryModel>
class histosupp
{
public:
    //constructeurs
    histosupp();
    histosupp(QString);



    //getters
    QString getidhs();//accées lecture//récupérer la valeur d'un attribut


    //setters
    void setidhs(QString);



    //méthodes
    bool ajoutSupp();
    QSqlQueryModel * affichSupp();


    bool modifier();


    //métiers

private:

    QString idhs;

};


#endif // HISTOSUPP_H

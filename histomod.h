#ifndef HISTOMOD_H
#define HISTOMOD_H
#include <QString>
#include<QDate>
#include<QSqlQuery>
#include <QSqlQueryModel>
class histomod
{
public:
    //constructeurs
    histomod();
    histomod(QString,QString,int,int,int,QString,QDate);



    //getters
    QString getidh();//accées lecture//récupérer la valeur d'un attribut
    QString getnomh();
    int getqteh();
    QDate getdateh();
    QString getgenreh();
    int getpoidsh();
    int gettailleh();

    //setters
    void setidh(QString);
    void setnomh(QString);
    void setqteh(int);
    void setdateh(QDate);//demande changement d'etats//modifier un attribut
    void setgenreh(QString);
    void setpoidsh(int);
    void settailleh(int);


    //méthodes
    bool ajouter();
    QSqlQueryModel * afficher();


    bool modifier();


    //métiers

private:
    int quantiteh,poidsh,tailleh;
    QString nomh,genreh,idh;
    QDate dateph;
};
#endif // HISTOMOD_H

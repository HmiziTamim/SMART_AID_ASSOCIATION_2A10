#include "patient.h"
Patient::Patient()
{
CINP="";
NOMP="";
PRENOMP="";
ADRESSEP="";
ETATP="";
AGEP="";
}
Patient::Patient(QString CINP,QString NOMP,QString PRENOMP,QDate DATE_NAISSANCEP,QString ADRESSEP,QString ETATP,QString AGEP){
    this->CINP=CINP ;
    this->NOMP=NOMP ;
    this->PRENOMP=PRENOMP ;
    this->DATE_NAISSANCEP=DATE_NAISSANCEP ;
    this->ADRESSEP=ADRESSEP ;
    this->ETATP=ETATP ;
    this->AGEP=AGEP ;
}
QString Patient::getCINP(){return CINP ;}
QString Patient::getNOMP(){return NOMP ;}
QString Patient::getPRENOMP(){return PRENOMP ;}
QDate Patient::getDATE_NAISSANCEP(){return DATE_NAISSANCEP ;}
QString Patient::getADRESSEP(){return ADRESSEP ;}
QString Patient::getETATP(){return ETATP ;}
QString Patient::getAGEP(){return AGEP ;}
void Patient::setCINP (QString CINP){this->CINP=CINP ;}
void Patient::setNOMP (QString NOMP){this->NOMP=NOMP ;}
void Patient::setPRENOMP (QString PRENOMP){this->PRENOMP=PRENOMP ;}
void Patient::setDATE_NAISSANCEP (QDate DATE_NAISSANCEP){this->DATE_NAISSANCEP=DATE_NAISSANCEP ;}
void Patient::setADRESSEP (QString ADRESSEP){this->ADRESSEP=ADRESSEP ;}
void Patient::setETATP (QString ETATP){this->ETATP=ETATP ;}
void Patient::setAGEP (QString AGEP){this->AGEP=AGEP ;}
bool Patient::ajouter(){
    QSqlQuery query;
    query.prepare("INSERT INTO PATIENT (CINP,NOMP,PRENOMP,DATE_NAISSANCEP,ADRESSEP,ETATP,AGEP) "
                  "VALUES (:CINP,:NOMP,:PRENOMP,:DATE_NAISSANCEP,:ADRESSEP,:ETATP,:AGEP)");
    query.bindValue(":CINP", CINP);
    query.bindValue(":NOMP", NOMP);
    query.bindValue(":PRENOMP", PRENOMP);
    query.bindValue(":DATE_NAISSANCEP", DATE_NAISSANCEP);
    query.bindValue(":ADRESSEP",ADRESSEP);
    query.bindValue(":ETATP", ETATP);
    query.bindValue(":AGEP", AGEP);
    return  query.exec();
}
QSqlQueryModel* Patient::afficher(){
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM PATIENT");
    return model;
}
bool Patient::supprimer(QString CINP){
    QSqlQuery query;
    query.prepare("DELETE FROM PATIENT WHERE CINP=:CINP");
    query.bindValue(":CINP",CINP);
    return  query.exec();
}

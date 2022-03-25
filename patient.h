#ifndef PATIENT_H
#define PATIENT_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
class Patient
{
public:
    Patient();
    Patient(QString,QString,QString,QDate,QString,QString,QString);
    QString getCINP();
    QString getNOMP();
    QString getPRENOMP();
    QDate getDATE_NAISSANCEP();
    QString getADRESSEP();
    QString getETATP();
    QString getAGEP();
    void setCINP (QString);
    void setNOMP (QString);
    void setPRENOMP (QString);
    void setDATE_NAISSANCEP (QDate);
    void setADRESSEP (QString);
    void setETATP (QString);
    void setAGEP (QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool update();
    QSqlQueryModel * trierpatient1();
    QSqlQueryModel * trierpatient2();
    QSqlQueryModel * trierpatient3();
    QSqlQueryModel* recherche(QString NOMP);
    QSqlQueryModel* recherche2(QString CINP);
    QSqlQueryModel* recherche3(QString PRENOMP);

    void CREATION_PDF();
    private:
    QString CINP;
    QString NOMP;
    QString PRENOMP;
    QDate DATE_NAISSANCEP;
    QString ADRESSEP;
    QString ETATP;
    QString AGEP;
};
#endif // PATIENT_H

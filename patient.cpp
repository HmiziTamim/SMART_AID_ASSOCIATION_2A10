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
bool Patient::update()
{
    QSqlQuery  query;
query.prepare("UPDATE Patient SET CINP=:CINP ,NOMP=:NOMP, PRENOMP=:PRENOMP, DATE_NAISSANCEP=:DATE_NAISSANCEP, ADRESSEP=:ADRESSEP, ETATP=:ETATP, AGEP=:AGEP  where CINP=:CINP");
query.bindValue(":CINP", CINP);
query.bindValue(":NOMP", NOMP);
query.bindValue(":PRENOMP", PRENOMP);
query.bindValue(":DATE_NAISSANCEP", DATE_NAISSANCEP);
query.bindValue(":ADRESSEP",ADRESSEP);
query.bindValue(":ETATP", ETATP);
query.bindValue(":AGEP", AGEP);

return query.exec();
}
QSqlQueryModel *Patient::trierpatient1()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PATIENT ORDER BY NOMP ") ;
    return  model ;
}
QSqlQueryModel *Patient::trierpatient2()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PATIENT ORDER BY CINP") ;
    return  model ;
}
QSqlQueryModel *Patient::trierpatient3()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PATIENT ORDER BY PRENOMP") ;
    return  model ;
}

QSqlQueryModel* Patient::recherche(QString NOMP)

 {

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PATIENT WHERE(NOMP LIKE '%"+NOMP+"%')");
    return  model ;

}
QSqlQueryModel* Patient::recherche2(QString CINP){

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PATIENT WHERE(CINP = "+CINP+")");
    return  model ;

}
QSqlQueryModel* Patient::recherche3(QString PRENOMP)
 {

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PATIENT WHERE(PRENOMP LIKE '%"+PRENOMP+"%')");
    return  model ;

}
void Patient::CREATION_PDF()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QSqlQuery q;
    q.prepare("SELECT * FROM PATIENT ");
    q.exec();
    QString pdf="<br> <h1  style='color:blue'>LISTE DES Patients  <br></h1>\n <br> <table>  <tr>  <th>CINP </th> <th>NOMP </th> <th>PRENOMP  </th> <th>DATE_NAISSANCEP  </th><th>ADRESSEP  </th><th>ETATP  </th> <th>AGEP</th> </tr>" ;


    while ( q.next()) {


        pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toInt()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" <td>" +q.value(3).toString() +" <td>" +q.value(4).toString() +" <td>" +q.value(5).toString() +" "" " "</td> </td>" ;
    }
    doc.setHtml(pdf);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);


}

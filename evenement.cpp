#include "evenement.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QList>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
Evenement::Evenement()
{
id=0;
nom="";
type="";
lieu="";
//date_debut="";
//date_fin="";
}
Evenement::Evenement(int id,QString nom,QString type,QString lieu,QDate date_debut,QDate date_fin)
{this->id=id;this->nom=nom;this->type=type;this->lieu=lieu;this->date_debut=date_debut;this->date_fin=date_fin; }
int Evenement::getid(){return id;}
QString Evenement:: getnom(){return nom;}
QString Evenement:: gettype(){return type;}
QString Evenement:: getlieu(){return lieu;}
QDate Evenement:: getdate_debut(){return date_debut;}
QDate Evenement:: getdate_fin(){return date_fin;}
void Evenement:: setid(int id){this->id=id;}
void Evenement:: setnom(QString nom){this->nom=nom;}
void Evenement:: settype(QString type){this->type=type;}
void Evenement:: setlieu(QString lieu){this->lieu=lieu;}
void Evenement:: setdate_debut(QDate date_debut){this->date_debut=date_debut;}
void Evenement:: setdate_fin(QDate date_fin){this->date_fin=date_fin;}
bool Evenement:: ajouter()
{
QSqlQuery query;
QString id_string=QString::number(id);
      query.prepare("INSERT INTO EVENEMENT (id,nom,type,lieu,date_debut,date_fin) "
                    "VALUES (:id, :nom,:type,:lieu,:date_debut,:date_fin)");
      query.bindValue(":id",id_string );
      query.bindValue(":nom",nom);
      query.bindValue(":date_debut",date_debut);
      query.bindValue(":date_fin",date_fin);
      query.bindValue(":type",type);
      query.bindValue(":lieu",lieu);
      return query.exec();




}
bool Evenement::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from evenement where id=:id");
    query.bindValue(0,id);

    return query.exec();


}

QSqlQueryModel* Evenement::afficher()
{
 QSqlQueryModel* model=new QSqlQueryModel();
       model->setQuery("SELECT * FROM evenement ");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant "));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("lieu"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_debut"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_fin"));

return model;
}


bool Evenement::modifierEvent(int id)

{
    QSqlQuery query;

    query.prepare("update evenement set nom=:nom, type=:type, lieu=:lieu, date_debut=:date_debut,date_fin=:date_fin where id=:id");
    query.bindValue(":id",id );
    query.bindValue(":nom",nom);
    query.bindValue(":type",type);
    query.bindValue(":lieu",lieu);
    query.bindValue(":date_debut",date_debut);
    query.bindValue(":date_fin",date_fin);
    return query.exec();

}

QSqlQueryModel* Evenement::recherche(QString nom)

 {

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from evenement WHERE(nom  LIKE '%"+nom+"%')");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("lieu"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_debut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_fin"));
    return  model ;

}

QSqlQueryModel *Evenement::trierevenement1()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from evenement order by nom") ;
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("lieu"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_debut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_fin"));


    return  model ;

}

QSqlQueryModel *Evenement::trierevenement2()
{
    QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery("select * from evenement order by id ") ;
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("lieu"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_debut"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_fin"));
 return  model ;
}
void Evenement::CREATION_PDF()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QSqlQuery q;
    q.prepare("SELECT * FROM evenement ");
    q.exec();
    QString pdf="<br> <h1  style='color:blue'>LISTE DES Evenements  <br></h1>\n <br> <table>  <tr>  <th>ID </th> <th>NOM </th> <th>type  </th> <th>lieu  </th><th>date_debut  </th><th>date_fin  </th> </tr>" ;


    while ( q.next()) {


        pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toInt()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" <td>" +q.value(3).toString() +" <td>" +q.value(4).toString() +" <td>" +q.value(5).toString() +" "" " "</td> </td>" ;
    }
    doc.setHtml(pdf);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);


}


void Evenement::statistique(QWidget * w)
{
    int type1 = 0,type2=0,type3 =0;
        QSqlQuery query("SELECT COUNT(*) FROM evenement WHERE type='type1'");
        while(query.next())
        {
            type1 = query.value(0).toInt();
        }
        QSqlQuery query2("SELECT COUNT(*) FROM evenement WHERE type='type2'");
        while(query2.next())
        {
           type2 = query2.value(0).toInt();
        }
        QSqlQuery query3("SELECT COUNT(*) FROM evenement WHERE type='type3'");
        while(query3.next())
        {
           type3 = query3.value(0).toInt();
        }



    int total=(type1+type2+type3);

    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.28);
    //series->setPieSize(1.0);

    float val=(type1*100)/total;  //calcul du pourcentage
    QString nbre_string = QString::number(val);
series->append("type1 "+nbre_string+"%  ",type1);
   val=(type2*100)/total;  //calcul du pourcentage
   nbre_string = QString::number(val);
series->append("type2 "+nbre_string+"% ",type2);
    val=(type3*100)/total;  //calcul du pourcentage
    nbre_string = QString::number(val);
series->append("type3 "+nbre_string+"% ",type3);


QPieSlice * type1_s = series->slices().at(0);
QPieSlice * type2_s = series->slices().at(1);
QPieSlice * type3_s = series->slices().at(2);


type1_s->setLabelVisible(true);
type2_s->setLabelVisible(true);
type3_s->setLabelVisible(true);

    type1_s->setBrush(QColor::fromRgb(85, 31, 31));
    type2_s->setBrush(QColor::fromRgb(219, 70, 0));
type3_s->setBrush(QColor::fromRgb(160, 205, 120));



    QChart *chart = new QChart();
    chart->addSeries(series);
    //chart->setTitle("Statistique par type");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignLeft);
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView * chartview = new QChartView(chart);
    chartview->resize(w->width(),w->height());
    chartview->setParent(w);

}

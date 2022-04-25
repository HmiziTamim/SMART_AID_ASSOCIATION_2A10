#include "evenement.h"

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
    int Congres = 0,Don=0,Sensibilisation =0;
        QSqlQuery query("SELECT COUNT(*) FROM evenement WHERE type='Congres'");
        while(query.next())
        {
            Congres = query.value(0).toInt();
        }
        QSqlQuery query2("SELECT COUNT(*) FROM evenement WHERE type='Don'");
        while(query2.next())
        {
           Don = query2.value(0).toInt();
        }
        QSqlQuery query3("SELECT COUNT(*) FROM evenement WHERE type='Sensibilisation'");
        while(query3.next())
        {
           Sensibilisation = query3.value(0).toInt();
        }



    int total=(Congres+Don+Sensibilisation);

    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.28);
    //series->setPieSize(1.0);

    float val=(Congres*100)/total;  //calcul du pourcentage
    QString nbre_string = QString::number(val);
series->append("Congres "+nbre_string+"%  ",Congres);
   val=(Don*100)/total;  //calcul du pourcentage
   nbre_string = QString::number(val);
series->append("Don "+nbre_string+"% ",Don);
    val=(Sensibilisation*100)/total;  //calcul du pourcentage
    nbre_string = QString::number(val);
series->append("Sensibilisation "+nbre_string+"% ",Sensibilisation);


QPieSlice * Congres_s = series->slices().at(0);
QPieSlice * Don_s = series->slices().at(1);
QPieSlice * Sensibilisation_s = series->slices().at(2);


Congres_s->setLabelVisible(true);
Don_s->setLabelVisible(true);
Sensibilisation_s->setLabelVisible(true);

    Congres_s->setBrush(QColor::fromRgb(85, 31, 31));
    Don_s->setBrush(QColor::fromRgb(219, 70, 0));
Sensibilisation_s->setBrush(QColor::fromRgb(160, 205, 120));



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

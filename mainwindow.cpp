#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "volontaire.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QSqlQuery>
//PDF
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QTextStream>
#include <QPainter>
//Stat
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>

//end of classes

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItems(V.lister());
    ui->comboBox_2->addItems(V.lister());
    ui->comboBox_3->addItems(V.lister());
    ui->comboBox_4->addItems(V.listerEmail());

    ui->tab_volontaire->setModel(V.afficher());
    ui->le_id->setValidator(new QIntValidator(0,99999999, this));


    QRegExp rxEmail("\\b[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}\\b");
    QRegExp rxNom("^([a-zA-Z]{2,}\\s[a-zA-Z]{1,}'?-?[a-zA-Z]{2,}\\s?([a-zA-Z]{1,})?)");
    QRegExp rxNumTel("^[\\+]?[(]?[0-9]{3}[)]?[-\\s\\.]?[0-9]{3}[-\\s\\.]?[0-9]{4,6}$");
    QRegExp rxNum("[0-9]{4}");

    QRegExpValidator *valiEmail =new QRegExpValidator(rxEmail,this);
    QRegExpValidator *valiNom =new QRegExpValidator(rxNom,this);
    QRegExpValidator *valiNumTel =new QRegExpValidator(rxNumTel,this);
    QRegExpValidator *valiNum =new QRegExpValidator(rxNum,this);

    ui->le_email->setValidator(valiEmail);
    ui->le_nom->setValidator(valiNom);
    ui->le_prenom->setValidator(valiNom);
    ui->le_num->setValidator(valiNumTel);
    ui->lineEdit_4->setValidator(valiNum);

    ui->le_email_2->setValidator(valiEmail);
    ui->le_nom_2->setValidator(valiNom);
    ui->le_prenom_2->setValidator(valiNom);
    ui->le_num_2->setValidator(valiNumTel);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    QString id=ui->le_id->text();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QDate datedenaissance=ui->le_date->date();
    QString email=ui->le_email->text();
    QString adresse=ui->le_adresse->text();
    QString dispo=ui->cb_dispo->currentText();
    QString num=ui->le_num->text();

    if(email.contains(QRegExp("\\b[a-zA-Z0-9.%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4}\\b")))
{
   Volontaire V(id,nom,prenom,datedenaissance,adresse,email,dispo,num);
   bool test=V.ajouter();


   if(test)
   {
    QMessageBox::information(nullptr, QObject::tr("OK"),
           QObject::tr("Ajout effectué\n"
                       "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_volontaire->setModel(V.afficher());
    ui->comboBox->clear();
    ui->comboBox->addItems(V.lister());
    ui->comboBox_2->clear();
    ui->comboBox_2->addItems(V.lister());
   }
   else
   {
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
            QObject::tr("Ajout effectué\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
   }
}
    else
    {
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
             QObject::tr("Erreur valeur mail entrée erronée\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_supprimer_clicked()
{
    Volontaire V1;
    V1.setid(ui->comboBox->currentText());
    bool test=V1.supprimer(V1.getid());


    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("Suppression effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_volontaire->setModel(V.afficher());
        ui->comboBox->clear();
        ui->comboBox->addItems(V.lister());
        ui->comboBox_2->clear();
        ui->comboBox_2->addItems(V.lister());
        ui->comboBox_3->clear();
        ui->comboBox_3->addItems(V.lister());
        ui->comboBox_4->clear();
        ui->comboBox_4->addItems(V.listerEmail());
    }
     else
    {
        QMessageBox::information(nullptr, QObject::tr("Not Ok"),
             QObject::tr("Suppression non effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_pb_modifier_clicked()
{
    QString id =ui->comboBox_2->currentText();
    QString NOM=ui->le_nom_2->text();
    QString PRENOM=ui->le_prenom_2->text();
    QDate datedenaissance=ui->le_date_2->date();
    QString adresse=ui->le_adresse_2->text();
    QString email=ui->le_email_2->text();
    QString dispo=ui->cb_dispo_2->currentText();
    QString num=ui->le_num_2->text();

    Volontaire V1(id,NOM,PRENOM,datedenaissance,adresse,email,dispo,num);
    bool test=V1.update();

    if(test)
    {
     QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Modification effectué\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tab_volontaire->setModel(V.afficher());
     ui->comboBox->clear();
     ui->comboBox->addItems(V.lister());
     ui->comboBox_2->clear();
     ui->comboBox_2->addItems(V.lister());
     ui->comboBox_3->clear();
     ui->comboBox_3->addItems(V.lister());
     ui->comboBox_4->clear();
     ui->comboBox_4->addItems(V.listerEmail());
    }
    else
    {
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
             QObject::tr("Modification erronée\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }

}



void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    QString id =arg1;
    QString nom;
    QString prenom;
    QDate datedenaissance;
    QString email;
    QString adresse;
    QString dispo;
    QString num;
    V.recup(id,nom,prenom,datedenaissance,adresse,email,dispo,num);

    ui->le_nom_2->setText(nom);
    ui->le_prenom_2->setText(prenom);
    ui->le_date_2->setDate(datedenaissance);
    ui->le_adresse_2->setText(adresse);
    ui->le_email_2->setText(email);
    ui->cb_dispo_2->setCurrentText(dispo);
    ui->le_num_2->setText(num);

}

void MainWindow::on_le_rech_textChanged()
{
    V.clearTable(ui->tab_volontaire);
    QString rech=ui->le_rech->text();
    ui->tab_volontaire->setModel(V.rechercher(rech));
}



//Refresh Buttons
void MainWindow::on_pushButton_clicked()
{
    ui->tab_volontaire->setModel(V.afficher());
    ui->comboBox->clear();
    ui->comboBox->addItems(V.lister());
    ui->comboBox_2->clear();
    ui->comboBox_2->addItems(V.lister());
    ui->comboBox_3->clear();
    ui->comboBox_3->addItems(V.lister());
    ui->comboBox_4->clear();
    ui->comboBox_4->addItems(V.listerEmail());
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tab_volontaire->setModel(V.afficher());
    ui->comboBox->clear();
    ui->comboBox->addItems(V.lister());
    ui->comboBox_2->clear();
    ui->comboBox_2->addItems(V.lister());
    ui->comboBox_3->clear();
    ui->comboBox_3->addItems(V.lister());
    ui->comboBox_4->clear();
    ui->comboBox_4->addItems(V.listerEmail());
    ui->le_rech->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tab_volontaire->setModel(V.afficher());
    ui->comboBox->clear();
    ui->comboBox->addItems(V.lister());
    ui->comboBox_2->clear();
    ui->comboBox_2->addItems(V.lister());
    ui->comboBox_3->clear();
    ui->comboBox_3->addItems(V.lister());
    ui->comboBox_4->clear();
    ui->comboBox_4->addItems(V.listerEmail());
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void MainWindow::on_pb_tri_nom_clicked()
{
    ui->tab_volontaire->setModel(V.triNom());
}

void MainWindow::on_pb_tri_prenom_clicked()
{
    ui->tab_volontaire->setModel(V.triprenom());
}

void MainWindow::on_pb_tri_age_clicked()
{
    ui->tab_volontaire->setModel(V.tridatedenaissance());
}

void MainWindow::on_pb_pdf_clicked()
{
QString strStream;
QTextStream out(&strStream);

const int rowCount = ui->tab_volontaire->model()->rowCount();
const int columnCount = ui->tab_volontaire->model()->columnCount();
   out <<  "<html>\n"
                    "<head>\n"
                              "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                           <<  QString("<title>%1</title>\n").arg("strTitle")
                    <<  "</head>\n"

                       "<body bgcolor=#ffffff link=#5000A0>\n"

                             "<center> <H1>Liste des Volontaires</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                       // headers
                                out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                out<<"<cellspacing=10 cellpadding=3>";
                                for (int column = 0; column < columnCount; column++)
                                if (!ui->tab_volontaire->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tab_volontaire->model()->headerData(column, Qt::Horizontal).toString());
                                out << "</tr></thead>\n";

                                       // data table
                                 for (int row = 0; row < rowCount; row++) {
                                 out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                 for (int column = 0; column < columnCount; column++) {
                                 if (!ui->tab_volontaire->isColumnHidden(column)) {
                                 QString data = ui->tab_volontaire->model()->data(ui->tab_volontaire->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                               }
                                           }
                                           out << "</tr>\n";
                                       }
                                       out <<  "</table> </center>\n"
                          "</body>\n"
             "</html>\n";

QPrinter printer (QPrinter::PrinterResolution);
printer.setOutputFormat(QPrinter::PdfFormat);
printer.setOutputFileName("C:/Users/User/OneDrive/Bureau/Next/Atelier_Connexion/PDF/listeDesVolontaires.pdf");

QTextDocument doc;
doc.setHtml(strStream);
doc.print(&printer);
            QMessageBox::information(nullptr, QObject::tr("Impression du PDF "),
                                              QObject::tr("pdf enregistré.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}

int MainWindow::on_pb_cf_clicked()
{
   QString id= ui->comboBox_3->currentText();
   QString nom= ui->lineEdit_2->text();
   QString prenom= ui->lineEdit_3->text();
   QString points= ui->lineEdit_4->text();
   QPrinter printer;

   printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setOutputFileName("C:/Users/User/OneDrive/Bureau/Next/Atelier_Connexion/carteF/carte("+id+").pdf");
   QPainter painter;
   QImage carte("C:/Users/User/OneDrive/Bureau/Next/Atelier_Connexion/carte.png");
    if (! painter.begin(&printer)) { // failed to open file
              qWarning("failed to open file, is it writable?");
              return 1;
         }
          painter.setPen(Qt::red);
          painter.setFont(QFont("Corbel", 9, QFont::Bold));

          painter.drawImage(-20,-20,carte);
          painter.drawText(50, 140, "CIN : ");

          painter.drawText(50, 170, "Nom : ");
          painter.drawText(50, 200, "Prénom : ");
          painter.drawText(50, 230, "Nombre de points colléctés : ");
          painter.setPen(Qt::darkRed);
          painter.drawText(85, 140, id);
          painter.drawText(90, 170,nom );
          painter.drawText(110, 200, prenom);
          painter.setPen(Qt::darkRed);
          painter.drawText(240, 230, points);
          if (! printer.newPage()) {
              qWarning("failed in flushing page to disk, disk full?");
              return 1;
          }
          painter.drawText(10, 10, "Test");
          painter.end();
          QMessageBox::information(nullptr, QObject::tr("Impression du PDF "),
                                     QObject::tr("carte imprimé sur carteF .\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
          return 0;
}

void MainWindow::on_comboBox_3_currentTextChanged(const QString &arg1)
{

    QString id =arg1;
    QString nom;
    QString prenom;
    QDate datedenaissance;
    QString email;
    QString adresse;
    QString dispo;
    QString num;
    V.recup(id,nom,prenom,datedenaissance,adresse,email,dispo,num);

    ui->lineEdit_2->setText(nom);
    ui->lineEdit_3->setText(prenom);
}


void MainWindow::on_pb_mail_clicked()
{

    Smtp* smtp = new Smtp(ui->le_mail->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


        smtp->sendMail(ui->le_mail->text(), ui->comboBox_4->currentText() , ui->le_objet->text(),ui->te_message->toPlainText());

}

void MainWindow::mailSent(QString status)
{
        if(status == "Message sent")
            QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void MainWindow::on_pb_stat_clicked()
{
    QString h="Oui";
    QString f="Non";
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from Volontaire where dispo like '%"+h+"%'");
    float dispo1=model->rowCount();

    model->setQuery("select * from Volontaire where dispo like '%"+f+"%' ");
    float dispo=model->rowCount();

    float total=dispo1+dispo;
    QString a=QString("disponible . " +QString::number((dispo1*100)/total,'f',2)+"%" );
    QString b=QString("non disponible .  "+QString::number((dispo*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,dispo1);
    series->append(b,dispo);
    if (dispo1!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( dispo!=0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
    }

    QChart *chart = new QChart();
    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle("disponibilité des volontaires :Nb Volontaires: "+ QString::number(total));
    chart->legend()->hide();
    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}


void MainWindow::on_pb_stat_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from Volontaire where (extract(year from datedenaissance))<2002 ");
    float tranche_age1=model->rowCount();
    model->setQuery("select * from Volontaire where (extract(year from datedenaissance)) BETWEEN 1987 AND 2002 ");
    float tranche_age2=model->rowCount();
    model->setQuery("select * from Volontaire where (extract(year from datedenaissance))>1987 ");
   float tranche_age3=model->rowCount();

    float total=tranche_age1+tranche_age2+tranche_age3;
    QString a=QString("moins de 20 ans . "+QString::number((tranche_age1*100)/total,'f',2)+"%" );
    QString b=QString("entre 20 et 35 ans .  "+QString::number((tranche_age2*100)/total,'f',2)+"%" );
    QString c=QString("plus de 35 ans ."+QString::number((tranche_age3*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,tranche_age1);
    series->append(b,tranche_age2);
    series->append(c,tranche_age3);
    if (tranche_age1!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( tranche_age2!=0)
    {
        // Add label, explode and define brush for 2nd slice
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
    }
    if(tranche_age3!=0)
    {
        // Add labels to rest of slices
        QPieSlice *slice2 = series->slices().at(2);
        slice2->setLabelVisible();
    }

    // Create the chart widget
    QChart *chart = new QChart();
    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle("Age Par Pourcentage des Volontaires");
    chart->legend()->hide();
    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}


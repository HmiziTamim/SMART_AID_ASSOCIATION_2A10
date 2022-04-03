#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patient.h"
#include <QFile>
#include <QtWidgets/QApplication>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditCINP->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEditAGEP->setValidator(new QIntValidator(0,999,this));
    ui->lineEditSUPP->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEditCINP_2->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEditAGEP_2->setValidator(new QIntValidator(0,999,this));
    QRegExp rxnom("\\b[a-zA-Z]{2,20}\\b");
        QRegExpValidator *valinom =new QRegExpValidator(rxnom,this);
        ui->lineEditNOMP->setValidator(valinom);
        ui->lineEditNOMP_2->setValidator(valinom);
        ui->lineEditPRENOMP->setValidator(valinom);
        ui->lineEditPRENOMP_2->setValidator(valinom);
    ui->tableView->setModel(P.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonQuitter_clicked()
{
    this->close();
}

void MainWindow::on_pushButtonAjouter_clicked()
{
    QString CINP=ui->lineEditCINP->text();
    QString NOMP=ui->lineEditNOMP->text();
    QString PRENOMP=ui->lineEditPRENOMP->text();
    QDate DATE_NAISSANCEP=ui->dateEdit->date();
    QString ADRESSEP=ui->lineEditADRESSEP->text();
    QString ETATP=ui->lineEditETATP->text();
    QString AGEP=ui->lineEditAGEP->text();
    Patient P(CINP,NOMP,PRENOMP,DATE_NAISSANCEP,ADRESSEP,ETATP,AGEP);
    bool test=P.ajouter();
    if(test)
        {

        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Ajout effectué\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(P.afficher());
        }
        else
    {
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"), QObject::tr("Ajout non effectué\n""Click Cancel to exit."), QMessageBox::Cancel);

    }
}


void MainWindow::on_pushButtonSUPP_clicked()
{
    Patient P1 ;
    P1.setCINP(ui->lineEditSUPP->text());
    bool test=P1.supprimer(P1.getCINP());
    if(test)
        {
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("suppression  effectué\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(P.afficher());
        }
        else
    {
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"), QObject::tr("suppression non effectué\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButtonModifier_clicked()
{
    QString CINP=ui->lineEditCINP_2->text();
    QString NOMP=ui->lineEditNOMP_2->text();
    QString PRENOMP=ui->lineEditPRENOMP_2->text();
    QDate DATE_NAISSANCEP=ui->dateEdit_2->date();
    QString ADRESSEP=ui->lineEditADRESSEP_2->text();
    QString ETATP=ui->lineEditETATP_2->text();
    QString AGEP=ui->lineEditAGEP_2->text();

    Patient P2(CINP,NOMP,PRENOMP,DATE_NAISSANCEP,ADRESSEP,ETATP,AGEP);
    bool test=P2.update();

    if(test)
    {
     QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Modification effectué\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tableView->setModel(P.afficher());
    }
    else
    {
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
             QObject::tr("Modification erronée\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_triparid_clicked()
{
    Patient E ;
        ui->tableView->setModel(E.trierpatient1());
}

void MainWindow::on_pb_triparnom_clicked()
{
    Patient E ;
        ui->tableView->setModel(E.trierpatient2());
}

void MainWindow::on_pushButtonRECHERCHE_clicked()
{
    Patient E ;
         QString rech =ui->lineEditRECHERCHE->text();
         if (rech=="")

             ui->tableView->setModel(E.afficher());
         else
             ui->tableView->setModel(E.recherche(rech));
}

void MainWindow::on_pushButton_clicked()
{
    QString strStream;
        strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
            if (QFileInfo(strStream).suffix().isEmpty()) { strStream.append(".pdf"); }

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(strStream);



                  QTextStream out(&strStream);

                  const int rowCount = ui->tableView->model()->rowCount();
                  const int columnCount = ui->tableView->model()->columnCount();
                  QString TT = QDateTime::currentDateTime().toString();
                  out <<"<html>\n"
                        "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                      << "<title>PDF<title>\n "
                      << "</head>\n"
                      "<body bgcolor=#ffffff link=#5000A0>\n"
                         "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                      "<h1 style=\"text-align: center;\"><strong> ******LISTE DES PATIENT ****** </strong></h1>"

                      "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                        "</br> </br>";
                  // headers
                  out << "<thead><tr bgcolor=#d6e5ff>";
                  for (int column = 0; column < columnCount; column++)
                      if (!ui->tableView->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->tableView->isColumnHidden(column)) {
                              QString data =ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                          }
                      }
                      out << "</tr>\n";
                  }
                  out <<  "</table>\n"
                      "</body>\n"
                      "</html>\n";

                  QTextDocument document;
                  document.setHtml(strStream);
                  document.print(&printer);
}

void MainWindow::on_pushButtonSTAT_clicked()
{
    QString h="Oui";
    QString f="Non";
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from PATIENT where AGEP >= 18");
    float dispo1=model->rowCount();

    model->setQuery("select * from PATIENT where AGEP <18");
    float dispo=model->rowCount();

    float total=dispo1+dispo;
        QString a=QString("majeur . " +QString::number((dispo1*100)/total,'f',2)+"%" );
        QString b=QString("mineur .  "+QString::number((dispo*100)/total,'f',2)+"%" );
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
    chart->setTitle("age des patient :Nb patient: "+ QString::number(total));
    chart->legend()->hide();
    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}

void MainWindow::on_pushButtonRECHERCHE_2_clicked()
{
    Patient E ;
         QString rech =ui->lineEditRECHERCHE_2->text();
         if (rech=="")

             ui->tableView->setModel(E.afficher());
         else
             ui->tableView->setModel(E.recherche3(rech));
}

void MainWindow::on_pushButtonRECHERCHE_3_clicked()
{
    Patient E ;
         QString rech =ui->lineEditRECHERCHE_3->text();
         if (rech=="")

             ui->tableView->setModel(E.afficher());
         else
             ui->tableView->setModel(E.recherche2(rech));
}



void MainWindow::on_pb_triparprenom_clicked()
{
    Patient E ;
        ui->tableView->setModel(E.trierpatient3());
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/tamim/OneDrive/Documents/QT/QTDark.stylesheet")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/tamim/OneDrive/Documents/QT/Adaptic.qss")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/tamim/OneDrive/Documents/QT/Perstfic.qss")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_4_toggled(bool checked)
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/tamim/OneDrive/Documents/QT/Fibers.qss")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_9_toggled(bool checked)
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_11_toggled(bool checked)
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/tamim/OneDrive/Documents/QT/Wstartpage.qss")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_10_toggled(bool checked)
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/tamim/OneDrive/Documents/QT/VisualScript.qss")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_12_toggled(bool checked)
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/tamim/OneDrive/Documents/QT/Diplaytap.qss")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

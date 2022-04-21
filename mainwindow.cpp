#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_idevent->setValidator(new QIntValidator(0,9999,this));
    ui->tab_evenement->setModel(E.afficher());
    QRegExp rxnom("\\b[a-zA-Z0-9]{2,10}\\b");
        QRegExpValidator *valinom =new QRegExpValidator(rxnom,this);
        ui->le_nomevent->setValidator(valinom);
        ui->le_nom_2event->setValidator(valinom);
        ui->le_lieuevent->setValidator(valinom);
        ui->le_lieu_2event->setValidator(valinom);
        QRegExp rxtype("\\b[a-zA-Z0-9]{2,10}\\b");
            QRegExpValidator *valitype =new QRegExpValidator(rxtype,this);
            ui->le_typeevent->setValidator(valitype);
            ui->le_type_2event->setValidator(valitype);
            ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
            ui->quickWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouterevent_clicked()
{
    int id=ui->le_idevent->text().toUInt();
    QString nom=ui->le_nomevent->text();
    QString type=ui->le_typeevent->currentText();
    QString lieu=ui->le_lieuevent->text();
   QDate date_debut=ui->le_date_debut->date();
    QDate date_fin=ui->le_date_fin->date();


     Evenement E(id,nom,type,lieu,date_debut,date_fin);
     bool test=E.ajouter();
            if(test)
            {
             QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
             ui->tab_evenement->setModel(E.afficher());

            }
            else
            {
             QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                     QObject::tr("Ajout non effectué\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
            }
}


void MainWindow::on_le_supprimer_clicked()
{
Evenement E1; E1.setid(ui->le_id_suppevent->text().toInt()) ;
bool test=E1.supprimer(E1.getid());
QMessageBox msgBox;
if(test)
{
    msgBox.setText("Suppression  avec succes");
    ui->tab_evenement->setModel(E.afficher());
}
else
    msgBox.setText("Echec suppression");
msgBox.exec();
}

void MainWindow::on_pb_modifierevent_clicked()
{
    int id=ui->le_id_2event->text().toInt();
    QString nom=ui->le_nom_2event->text();
    QString type=ui->le_type_2event->currentText();
    QString lieu=ui->le_lieu_2event->text();

    QDate date_debut=ui->le_date_debut_2->date();
    QDate date_fin=ui->le_date_fin_2->date();



    Evenement E(id,nom,type,lieu,date_debut,date_fin);
    bool test=E.modifierEvent(id);
       if(test)
       {
        QMessageBox::information(nullptr, QObject::tr("OK"),
               QObject::tr("Modification effectué\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_evenement->setModel(E.afficher());
       }
       else
       {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Modification non effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
       }
}



void MainWindow::on_pb_rechercheevent_clicked()
{

     Evenement E ;
     QString rech =ui->rechercheevent->text();
     if (rech=="")

         ui->tab_evenement->setModel(E.afficher());
     else
         ui->tab_evenement->setModel(E.recherche(rech));
}

void MainWindow::on_pb_triparnomevent_clicked()
{
    Evenement E ;
    ui->tab_evenement->setModel(E.trierevenement1());
}

void MainWindow::on_pb_triparidevent_clicked()
{
    Evenement E ;
    ui->tab_evenement->setModel(E.trierevenement2());
}

void MainWindow::on_tab_evenement_activated(const QModelIndex &index)
{
    QString val=ui->tab_evenement->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from evenement where id='"+val+"' or nom='"+val+"' or type='"+val+"' or lieu='"+val+"'  " );
    if(qry.exec())
    {
    while(qry.next())
    {
        ui->le_id_2event->setText((qry.value(0).toString()));

        ui->le_nom_2event->setText(qry.value(1).toString());
        ui->le_type_2event->setCurrentText(qry.value(2).toString());
        ui->le_lieu_2event->setText(qry.value(3).toString());
       // ui->le_date_debut_2->setDate(qry.value(4).toDate());
        //ui->le_date_fin_2->setDate(qry.value(5).toDate());

    }
    }
}

void MainWindow::on_pb_pdfevent_clicked()
{
    QString strStream;
    strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
        if (QFileInfo(strStream).suffix().isEmpty()) { strStream.append(".pdf"); }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(strStream);



              QTextStream out(&strStream);

              const int rowCount = ui->tab_evenement->model()->rowCount();
              const int columnCount = ui->tab_evenement->model()->columnCount();
              QString TT = QDateTime::currentDateTime().toString();
              out <<"<html>\n"
                    "<head>\n"
                     "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                  << "<title>ERP - COMmANDE LIST<title>\n "
                  << "</head>\n"
                  "<body bgcolor=#ffffff link=#5000A0>\n"
                     "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                    +"<div style=\"text-align: center;\"><img src=C:/Users/amine/Desktop/SMART_AID_ASSOCIATION_2A10-Gestion-des-evenements/inf2.png /></div>"
                  "<h1 style=\"text-align: center;\"><strong> ******LISTE DES EVENEMENTS ****** </strong></h1>"

                  "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                    "</br> </br>";
              // headers
              out << "<thead><tr bgcolor=#d6e5ff>";
              for (int column = 0; column < columnCount; column++)
                  if (!ui->tab_evenement->isColumnHidden(column))
                      out << QString("<th>%1</th>").arg(ui->tab_evenement->model()->headerData(column, Qt::Horizontal).toString());
              out << "</tr></thead>\n";

              // data table
              for (int row = 0; row < rowCount; row++) {
                  out << "<tr>";
                  for (int column = 0; column < columnCount; column++) {
                      if (!ui->tab_evenement->isColumnHidden(column)) {
                          QString data =ui->tab_evenement->model()->data(ui->tab_evenement->model()->index(row, column)).toString().simplified();
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



void MainWindow::on_pb_changer_clicked()
{
    if (ui->comboBoxevent->currentText()=="ENG")
    {
        ui->tabWidget->setTabText(0,"Add event");
        ui->tabWidget->setTabText(1,"View event");
        ui->tabWidget->setTabText(2,"Update event");


        ui->label->setText("ID event");
        ui->label_2->setText("Name event");
        ui->label_3->setText("Type event");
        ui->label_4->setText("location event");
        ui->label_6->setText("Start date");
        ui->label_7->setText("End date");
        ui->pb_modifierevent->setText("Edit");
        ui->pb_ajouterevent->setText("Add");
        ui->pb_triparidevent->setText("Sort by id");
        ui->pb_triparnomevent->setText("Sort by name");
        ui->le_supprimer->setText("Delete");
        ui->pb_changer->setText("Change");
        ui->label_5->setText("ID event");
        ui->label_8->setText("Name event");
        ui->label_10->setText("Type event");
        ui->label_11->setText("Location event");
        ui->label_9->setText("Start date");
        ui->label_12->setText("End date");
        ui->label_19->setText("Add Event");
        ui->label_20->setText("Update Event");
        ui->pushButton_5->setText("Employees");
        ui->pushButton_6->setText("Voluntary");

        ui->pushButton_8->setText("Stock");
        ui->pushButton_9->setText("Events");









    }
    else if (ui->comboBoxevent->currentText()=="FR")
    {
        ui->tabWidget->setTabText(0,"Ajouter evenement");
        ui->tabWidget->setTabText(1,"Afficher evenement");
        ui->tabWidget->setTabText(2,"Modifier evenement");

        ui->label->setText("ID evenement");
        ui->label_2->setText("Nom evenement");
        ui->label_3->setText("Type evenement");
        ui->label_4->setText("Lieu evenement");
        ui->label_6->setText("date debut");
        ui->label_7->setText("date fin");
        ui->pb_modifierevent->setText("modifier");
        ui->pb_ajouterevent->setText("Ajouter");
        ui->pb_triparidevent->setText("tri_par_id");
        ui->pb_triparnomevent->setText("tri_par_nom");
        ui->le_supprimer->setText("supprimer");
        ui->pb_changer->setText("changer");
        ui->label_5->setText("ID evenement");
        ui->label_8->setText("Nom evenement");
        ui->label_10->setText("Type evenement");
        ui->label_11->setText("Lieu evenement");
        ui->label_9->setText("date debut");
        ui->label_12->setText("date fin");
        ui->pushButton_5->setText("Employés");
        ui->pushButton_6->setText("Volontaire");

        ui->pushButton_8->setText("Produit");
        ui->pushButton_9->setText("Evenements");
        ui->label_19->setText("Ajouter un evenement");
        ui->label_20->setText("Modifier un evenement");





    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    E.statistique(ui->widget);
}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    E.statistique(ui->widget);
}

















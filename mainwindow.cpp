#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "employe.h"
#include "volontaire.h"
#include "patient.h"
#include "evenement.h"

#include <QString>
#include<QMessageBox>
#include<QIntValidator>
#include <QtGui>
#include<QSqlQuery>
#include<QPrinter>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
#include <QMediaPlayer>
#include <QTcpSocket>
#include <QTextStream>
#include "dumessageconnectiondialog.h"

//PDF
#include <QPrinter>
#include <QTextDocument>
#include <QTextStream>
#include <QPainter>

/*******sarra*********/
QT_CHARTS_USE_NAMESPACE


double calcVal = 0.0;

// Will define if this was the last math button clicked
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;



using namespace qrcodegen;
using namespace std;

/***************************/


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mSocket=new QTcpSocket(this);
    connect(mSocket,&QTcpSocket::readyRead,[&](){
        QTextStream T(mSocket);
        auto text = T.readAll();
        ui->textEdit->append(text);
    });

    //******************* KOUSSAY *******************
    ui->le_cin->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_tel->setValidator(new QIntValidator(0, 99999999, this));
   ui->le_etat->setValidator(new QIntValidator(0, 99999, this));
    QRegExp rxnom("\\b[a-zA-Z]{2,50}\\b");
        QRegExpValidator *valinom =new QRegExpValidator(rxnom,this);
        ui->le_nom->setValidator(valinom);
        ui->le_prenom->setValidator(valinom);
        ui->le_nat->setValidator(valinom);
        ui->le_adresse->setValidator(valinom);
        ui->le_mod_nom->setValidator(valinom);
        ui->le_mod_prenom->setValidator(valinom);
        ui->le_mod_nat->setValidator(valinom);
        ui->le_mod_adresse->setValidator(valinom);
    QRegExp rxEmail("\\b[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4}\\b");
    QRegExpValidator *valiEmail =new QRegExpValidator(rxEmail,this);
    ui->le_email->setValidator(valiEmail);

    ui->tab_employe->setModel(e.afficher());

     //******************* lim3allem *******************
    ui->comboBox_2->addItems(V.lister());
     ui->comboBox_3->addItems(V.lister());
     ui->comboBox_4->addItems(V.lister());
     ui->comboBox_5->addItems(V.listerEmail());

     ui->tab_volontaire->setModel(V.afficher());
     ui->le_id->setValidator(new QIntValidator(0,99999999, this));


     //QRegExp rxEmail("\\b[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}\\b");
     QRegExp rxNom("^([a-zA-Z]{2,}\\s[a-zA-Z]{1,}'?-?[a-zA-Z]{2,}\\s?([a-zA-Z]{1,})?)");
     QRegExp rxNumTel("^[\\+]?[(]?[0-9]{3}[)]?[-\\s\\.]?[0-9]{3}[-\\s\\.]?[0-9]{4,6}$");
     QRegExp rxNum("[0-9]{4}");

     //QRegExpValidator *valiEmail =new QRegExpValidator(rxEmail,this);
     QRegExpValidator *valiNom =new QRegExpValidator(rxNom,this);
     QRegExpValidator *valiNumTel =new QRegExpValidator(rxNumTel,this);
     QRegExpValidator *valiNum =new QRegExpValidator(rxNum,this);

     ui->le_email_2->setValidator(valiEmail);
     ui->le_nom_2->setValidator(valiNom);
     ui->le_prenom_2->setValidator(valiNom);
     ui->le_num_2->setValidator(valiNumTel);
     ui->lineEdit_4->setValidator(valiNum);

     ui->le_email_3->setValidator(valiEmail);
     ui->le_nom_3->setValidator(valiNom);
     ui->le_prenom_3->setValidator(valiNom);
     ui->le_num_6->setValidator(valiNumTel);


     ui->signup_cin->setValidator(valiNum);
     ui->login_cin->setValidator(valiNum);
    ui->signup_username->setValidator(valiNom);
    ui->signup_email->setValidator(valiEmail);

     ui->radioButton_2->setChecked(true);
     serial = new QSerialPort(); //Initialiser la variable Serial
     arduino_available = false;

     foreach (const QSerialPortInfo &serial_Info, QSerialPortInfo::availablePorts()) {//Lire l'información de chaque port serial
        // qDebug()<<"port: "<<serial_Info.portName();
         portname = serial_Info.portName();
        // qDebug()<<"Vendor Id: "<<serial_Info.vendorIdentifier();
         vendorId = serial_Info.vendorIdentifier();
        // qDebug()<<"Product Id: "<<serial_Info.productIdentifier();
         productId = serial_Info.productIdentifier();

     }
      arduino_available = true;
     if(arduino_available){
         arduino_init();
     }
     tem=true;




     //******************* Tamim *******************
     ui->lineEditCINP_7->setValidator(new QIntValidator(0,99999999,this));
     ui->lineEditAGEP_7->setValidator(new QIntValidator(0,999,this));
     ui->lineEditSUPP_4->setValidator(new QIntValidator(0,99999999,this));
     ui->lineEditCINP_8->setValidator(new QIntValidator(0,99999999,this));
     ui->lineEditAGEP_8->setValidator(new QIntValidator(0,999,this));

         ui->lineEditNOMP_7->setValidator(valinom);
         ui->lineEditNOMP_8->setValidator(valinom);
         ui->lineEditPRENOMP_7->setValidator(valinom);
         ui->lineEditPRENOMP_8->setValidator(valinom);
     ui->tableView_4->setModel(P.afficher());


       //******************* Larbi *******************

        ui->le_idevent->setValidator(new QIntValidator(0,9999,this));
        ui->tab_evenement->setModel(E.afficher());
         ui->le_nomevent->setValidator(valinom);
         ui->le_nom_2event->setValidator(valinom);
         ui->le_lieuevent->setValidator(valinom);
         ui->le_lieu_2event->setValidator(valinom);
         QRegExp rxtype("\\b[a-zA-Z0-9]{2,10}\\b");
         QRegExpValidator *valitype =new QRegExpValidator(rxtype,this);
             ui->le_typeevent->setValidator(valitype);
             ui->le_type_2event->setValidator(valitype);
              ui->quickWidgetevent->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
             ui->quickWidgetevent->show();
 //**********************Hidden*********************
             ui->pb_sarr->setVisible(false);
              ui->pb_tamim->setVisible(false);
              ui->pb_larbi->setVisible(false);
              ui->pb_amine->setVisible(false);
             ui-> pb_kouss->setVisible(false);
             ui->logout->setVisible(false);
             ui->logosmart->setVisible(false);
             ui->sac->setVisible(false);
             ui->toolButton->setVisible(false);


           t=true;

             //**********************Sarra*********************

                  int ret=A.connect_arduino(); // lancer la connexion à arduino
                  switch(ret){
                  case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                      break;
                  case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                     break;
                  case(-1):qDebug() << "arduino is not available";
                  }
                 // QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label2())); // permet de lancer
                   //le slot update_label suite à la reception du signal readyRead (reception des données).
                  QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer

                  ui->le_idpr_5->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
                  ui->la_qtepr_5->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
                  ui->le_poidspr_5->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
                  ui->la_taillepr_5->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
                  ui->le_nompr_5->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z]{7}")));
                  ui->le_genrepr_5->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z]{6}")));

                  ui->le_id_supppr_5->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));

                  ui->id_modpr_5->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
                  ui->qte_modpr_5->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
                  ui->poids_modpr_5->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
                  ui->taille_modpr_5->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
                  ui->nom_modpr_5->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z]{7}")));
                  ui->genre_modpr_5->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z]{6}")));




                  ui->le_idpr_5->setPlaceholderText("Entrez le id...");
                  ui->le_nompr_5->setPlaceholderText("Entrez le nom...");
                  ui->le_genrepr_5->setPlaceholderText("Entrez le genre...");
                  ui->la_qtepr_5->setPlaceholderText("Entrez la quantite...");
                  ui->le_poidspr_5->setPlaceholderText("Entrez le poids...");
                  ui->la_taillepr_5->setPlaceholderText("Entrez la taille...");

                  ui->le_id_supppr_5->setPlaceholderText("Entrez le id à supprimer...");

                  ui->id_modpr_5->setPlaceholderText("Entrez le id...");
                  ui->nom_modpr_5->setPlaceholderText("Entrez le nom...");
                  ui->genre_modpr_5->setPlaceholderText("Entrez le genre...");
                  ui->qte_modpr_5->setPlaceholderText("Entrez la quantite...");
                  ui->poids_modpr_5->setPlaceholderText("Entrez le poids...");
                  ui->taille_modpr_5->setPlaceholderText("Entrez la taille...");




                  ui->tab_stock_5->setModel(S.afficher());
                ui->tab_hispr_5->setModel(H.afficherHistorique());


                  ui->Display_5->setText(QString::number(calcVal));

                      // Will hold references to all the number buttons
                      QPushButton *numButtons[10];

                      // Cycle through locating the buttons
                      for(int i = 0; i < 10; ++i){
                          QString butName = "Button" + QString::number(i) +"_5" ;

                          // Get the buttons by name and add to array
                          numButtons[i] = MainWindow::findChild<QPushButton *>(butName);

                          // When the button is released call num_pressed()
                          connect(numButtons[i], SIGNAL(released()), this,
                                  SLOT(NumPressed()));
                      }

                      // Connect signals and slots for math buttons
                      connect(ui->Add_5, SIGNAL(released()), this,
                              SLOT(MathButtonPressed()));
                      connect(ui->Subtract_5, SIGNAL(released()), this,
                              SLOT(MathButtonPressed()));
                      connect(ui->Multiply_5, SIGNAL(released()), this,
                              SLOT(MathButtonPressed()));
                      connect(ui->Divide_5, SIGNAL(released()), this,
                              SLOT(MathButtonPressed()));

                      // Connect equals button
                      connect(ui->Equals_5, SIGNAL(released()), this,
                              SLOT(EqualButtonPressed()));

                      // Connect change sign
                      connect(ui->ChangeSign_5, SIGNAL(released()), this,
                              SLOT(ChangeNumberSign()));




}

MainWindow::~MainWindow()
{
    delete ui;
}

    //******************* Bouttons *******************


void MainWindow::on_pb_kouss_clicked()
{
    ui->STW->setCurrentIndex(2);
}
void MainWindow::on_pb_amine_clicked()
{
    ui->STW->setCurrentIndex(3);
}
void MainWindow::on_pb_larbi_clicked()
{
    ui->STW->setCurrentIndex(6);
}
void MainWindow::on_pb_tamim_clicked()
{
    ui->STW->setCurrentIndex(4);
}
void MainWindow::on_pb_sarr_clicked()
{
    ui->STW->setCurrentIndex(5);
}
void MainWindow::on_toolButton_2_pressed()
{
    ui->toolButton->setVisible(true);
    ui->toolButton_2->setVisible(false);
    ui->signup_password->setEchoMode(QLineEdit::Normal);

}
void MainWindow::on_toolButton_pressed()
{
    ui->toolButton->setVisible(false);
    ui->toolButton_2->setVisible(true);
    ui->signup_password->setEchoMode(QLineEdit::Password);

}
void MainWindow::on_toolButton_4_pressed()
{
    ui->toolButton_3->setVisible(true);
    ui->toolButton_4->setVisible(false);
    ui->login_password->setEchoMode(QLineEdit::Normal);

}
void MainWindow::on_toolButton_3_pressed()
{
    ui->toolButton_3->setVisible(false);
    ui->toolButton_4->setVisible(true);
    ui->login_password->setEchoMode(QLineEdit::Password);

}


//******************* KOUSSAY *******************
void MainWindow::on_ajouter_clicked()
{

    QString cin=ui->le_cin->text();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString nat=ui->le_nat->text();
    QString etat=ui->le_etat->text();
    QDate naiss=ui->le_date->date();
    QString email=ui->le_email->text();
    QString adresse=ui->le_adresse->text();
    int tel=ui->le_tel->text().toInt();
    QString sexe=ui->comboBox->currentText();
    QMediaPlayer * music =new  QMediaPlayer;
    if(email.contains(QRegExp("\\b[a-zA-Z0-9.%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4}\\b")))
    {
    Employe e(cin,nom,prenom,nat,etat,email,naiss,adresse,tel,sexe);
    bool test=e.ajouter();
       if(test)
       {
        QMessageBox::information(nullptr, QObject::tr("OK"),
               QObject::tr("Ajout effectué\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_employe->setModel(e.afficher());
        music->setMedia(QUrl("qrc:/music/ajout succe.mp3"));

        music->play();
       }
       else
       {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Ajout non effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
       }
}else
    {
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
             QObject::tr("L'email doit contenir @\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_supp_clicked()
{

    QString cin =ui->le_id_supp->text();
   Employe e1; e1.setcin(cin);

   bool test=e1.supprimer(e1.getcin());
   if(test)
   {
    QMessageBox::information(nullptr, QObject::tr("OK"),
           QObject::tr("Suppression effectué\n"
                       "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_employe->setModel(e.afficher());
   }
   else
   {
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
            QObject::tr("Suppression n'est pas effectué\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
   }


}



void MainWindow::on_pushButton_10_clicked()
{
    this->close();
}

void MainWindow::on_quitter_clicked()
{
    this->close();
}


void MainWindow::on_pushButton_4_clicked()
{
    QString cin=ui->le_mod_cin->text();
    QString nom=ui->le_mod_nom->text();
    QString prenom=ui->le_mod_prenom->text();
    QString nat=ui->le_mod_nat->text();
    QString etat=ui->le_mod_etat->text();
    QString email=ui->le_mod_email->text();
    QDate naiss=ui->le_mod_date->date();
    QString adresse=ui->le_mod_adresse->text();
    int tel=ui->le_mod_tel->text().toInt();
    QString sexe=ui->comboBox_mod->currentText();
    Employe e(cin,nom,prenom,nat,etat,email,naiss,adresse,tel,sexe);
    bool test=e.modifier(cin);
       if(test)
       {
        QMessageBox::information(nullptr, QObject::tr("OK"),
               QObject::tr("Modification effectué\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_employe->setModel(e.afficher());
       }
       else
       {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Modification non effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
       }
}

void MainWindow::on_tab_employe_activated(const QModelIndex &index)
{
    QString val=ui->tab_employe->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from employe where cin='"+val+"' or nom='"+val+"' or prenom='"+val+"' or nat='"+val+"' or etat='"+val+"' or email='"+val+"' or adresse='"+val+"' or tel='"+val+"'");
    if(qry.exec())
    {
    while(qry.next())
    {
        ui->le_mod_cin->setText((qry.value(0).toString()));
        ui->le_id_supp->setText(qry.value(0).toString());
        ui->le_mod_nom->setText(qry.value(1).toString());
        ui->le_mod_prenom->setText(qry.value(2).toString());
        ui->le_mod_nat->setText(qry.value(3).toString());
        ui->le_mod_etat->setText(qry.value(4).toString());
        ui->le_mod_email->setText(qry.value(5).toString());
        ui->le_mod_adresse->setText(qry.value(7).toString());
        ui->le_mod_tel->setText(qry.value(8).toString());

    }
    }
}


void MainWindow::on_tri_cb_clicked()
{
    QString tri=ui->cb_tri->currentText();
    if(tri=="Nom")
         ui->tab_employe->setModel(e.triNom());
    else if(tri=="Prenom")
         ui->tab_employe->setModel(e.triprenom());
    else if(tri=="CIN")
        ui->tab_employe->setModel(e.tricin());
    else if(tri=="Telephone")
        ui->tab_employe->setModel(e.tritel());
    else if(tri=="Adresse")
        ui->tab_employe->setModel(e.triadresse());
    else if(tri=="Email")
        ui->tab_employe->setModel(e.triemail());
    else if(tri=="Nationnalité")
        ui->tab_employe->setModel(e.trinat());

}

void MainWindow::on_pb_rech_clicked()
{
    e.clearTable(ui->tab_employe);
    QString rech=ui->le_rech->text();
     ui->tab_employe->setModel(e.rechercher(rech));
}

void MainWindow::on_pdf_clicked()
{
    int id=ui->le_id_supp->text().toInt();
    int h=ui->le_h->text().toInt();
    int abs=ui->le_abs->text().toInt();
        QPdfWriter pdf("C:/Users/User/OneDrive/Bureau/Integration/Final0/PDF/ficheKOUSS.pdf");
        QPainter painter(&pdf);
       int i = 6700;
            painter.setPen(Qt::red);
            painter.setFont(QFont("MS Shell Dlg 2", 30));
            painter.drawText(3300,1100,"Fiche de paie ");
            painter.setPen(Qt::blue);
            painter.setFont(QFont("Comic Sans MS", 50));
            //painter.drawRect(1000,50,7300,1900);
            painter.setPen(Qt::black);
            painter.drawPixmap(QRect(4200,70,2600,2200),QPixmap("‪C:/Users/User/OneDrive/Bureau/Integration/Final0/inf.png"));
            painter.setPen(Qt::blue);
            painter.setFont(QFont("MS Shell Dlg 2", 15));
            painter.drawText(500,2300,"Identifiant: ");
            painter.drawText(500,2600,"Nom: ");
            painter.drawText(500,2900,"Prenom: ");
            painter.drawText(500,3200,"Nationnalité: ");
            painter.drawText(500,3500,"Email: ");
            painter.drawText(500,3800,"Date de naissance: ");
            painter.drawText(500,4100,"Adresse: ");
            painter.drawText(500,4400,"Telephone: ");
            painter.drawText(500,4700,"Genre: ");
            painter.drawRect(480,5800,7000,290);
            painter.drawRect(480,6090,7000,290);
            painter.drawRect(480,6380,7000,290);
            painter.drawRect(480,6670,7000,290);
            painter.drawRect(480,6960,7000,290);
            painter.drawRect(2800,7600,2900,290);
            painter.drawRect(3580,5800,0,5*290);
            painter.setPen(Qt::black);
            painter.drawText(500,6000,"Salaire de base: ");
            painter.setPen(Qt::darkRed);
            painter.drawText(500,6300,"Assurence medicale (-5%): ");
            painter.drawText(500,6600,"Assurence viellesse (-5%): ");
            painter.setPen(Qt::darkGreen);
            painter.drawText(500,6900,"Heures supplementaires: ");
            painter.setPen(Qt::darkRed);
            painter.drawText(500,7200,"Absence: ");
            painter.setPen(Qt::black);
            painter.drawText(2900,7800,"Salaire net: ");
            QSqlQuery query;
            query.prepare("select * from employe where cin=:id");
            query.bindValue(":id",id);
            query.exec();
            while (query.next())
            {
                int k=query.value(0).toInt();
                int salaire=query.value(4).toInt();
                char sal[50];
                char o[50];
                char s1[50];
                char v1[50];
                int s=salaire-(salaire*5)/100;
                int v=s-(s*5)/100;
                int hs=v+h*50;
                int ab=hs-abs*40;
                char abb[50];
                char hs1[50];
                itoa (hs,hs1,10);
                itoa(ab,abb,10);
                itoa(v,v1,10);
                itoa(k, o, 10);
                itoa(salaire,sal,10);
                itoa(s,s1,10);        
                painter.setPen(Qt::red);
                painter.drawText(i,2300,o);
                painter.setPen(Qt::black);
                painter.drawText(i,2600,query.value(1).toString());
                painter.drawText(i,2900,query.value(2).toString());
                painter.drawText(i,3200,query.value(3).toString());
                painter.drawText(i,3500,query.value(5).toString());
                painter.drawText(i,3800,query.value(6).toString());
                painter.drawText(i,4100,query.value(7).toString());
                painter.drawText(i,4400,query.value(8).toString());
                painter.drawText(i,4700,query.value(9).toString());
                painter.drawText(i,6000,sal);
                painter.drawText(i,6300,s1);
                painter.drawText(i,6600,v1);
                painter.drawText(i,6900,hs1);
                painter.drawText(i,7200,abb);
                painter.drawText(5000,7800,abb);

                painter.setPen(Qt::blue);
               i = i + 500;
            }
            int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                if (reponse == QMessageBox::Yes)
                {
                    QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/User/OneDrive/Bureau/Integration/Final0/PDF/ficheKOUSS.pdf"));
                    painter.end();
                }
                if (reponse == QMessageBox::No)
                {
                     painter.end();
                }

}



/*void MainWindow::on_pdf_2_clicked()
{
    QString h="Oui";
    QString f="Non";
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from Volontaire where dispo like '%"+h+"%'");
    float tranche_age1=model->rowCount();
    model->setQuery("select * from Volontaire where dispo like '%"+f+"%' ");
    float tranche_age2=model->rowCount();
    float total=tranche_age1+tranche_age2;
    QString a=QString("disponible . "+QString::number((tranche_age1100)/total,'f',2)+"%" );
    QString b=QString("non disponible .  "+QString::number((tranche_age2100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,tranche_age1);
    series->append(b,tranche_age2);
    if (tranche_age1!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( tranche_age2!=0)
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

}*/

void MainWindow::on_stat_clicked()
{
    QString h="Homme";
    QString f="Femme";
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from employe where sexe like '%"+h+"%'");
    float tranche_age1=model->rowCount();
    model->setQuery("select * from employe where sexe like '%"+f+"%' ");
    float tranche_age2=model->rowCount();
    float total=tranche_age1+tranche_age2;
    QString a=QString("homme . "+QString::number((tranche_age1*100)/total,'f',2)+"%" );
    QString b=QString("femme .  "+QString::number((tranche_age2*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,tranche_age1);
    series->append(b,tranche_age2);
    if (tranche_age1!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( tranche_age2!=0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
    }

    QChart *chart = new QChart();
    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle("Nombre des employés: "+ QString::number(total));
    chart->legend()->hide();
    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}


void MainWindow::on_le_rech_textChanged(const QString &arg1)
{
    Employe e;
        ui->tab_employe->setModel( e.rechercher(arg1));
}


void MainWindow::on_ajouter_image_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (QString::compare(filename, QString())!=0)
    {
        QImage image;
        bool valid= image.load(filename);
        if(valid)
        {
            image=image.scaledToWidth(ui->lbl_image->width(), Qt::SmoothTransformation);
            ui->lbl_image->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            //Error handling
        }
    }

}





void MainWindow::on_send_clicked()
{
    QTextStream T(mSocket);
    T<<ui->nickname->text()<<":"<<ui->message->text();
    mSocket->flush();
    ui->message->clear();
}


void MainWindow::on_bind_clicked()
{
    DuMessageConnectionDialog D(this);
    if(D.exec()==QDialog::Rejected)
    {
        return;
    }
    mSocket->connectToHost(D.hostname(),D.port());
}

  //******************* lim3allem *******************

void MainWindow::on_pb_ajouter_clicked()
{
    QString id=ui->le_id->text();
    QString nom=ui->le_nom_2->text();
    QString prenom=ui->le_prenom_2->text();
    QDate datedenaissance=ui->le_date_2->date();
    QString email=ui->le_email_2->text();
    QString adresse=ui->le_adresse_2->text();
    QString dispo=ui->cb_dispo_2->currentText();
    QString num=ui->le_num_2->text();

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
    ui->comboBox_2->clear();
    ui->comboBox_2->addItems(V.lister());
    ui->comboBox_3->clear();
    ui->comboBox_3->addItems(V.lister());
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
    V1.setid(ui->comboBox_2->currentText());
    bool test=V1.supprimer(V1.getid());


    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("Suppression effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_volontaire->setModel(V.afficher());
        ui->comboBox_2->clear();
        ui->comboBox_2->addItems(V.lister());
        ui->comboBox_3->clear();
        ui->comboBox_3->addItems(V.lister());
        ui->comboBox_4->clear();
        ui->comboBox_4->addItems(V.lister());
        ui->comboBox_5->clear();
        ui->comboBox_5->addItems(V.listerEmail());
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
    QString id =ui->comboBox_3->currentText();
    QString NOM=ui->le_nom_3->text();
    QString PRENOM=ui->le_prenom_3->text();
    QDate datedenaissance=ui->le_date_3->date();
    QString adresse=ui->le_adresse_3->text();
    QString email=ui->le_email_3->text();
    QString dispo=ui->cb_dispo_6->currentText();
    QString num=ui->le_num_6->text();

    Volontaire V1(id,NOM,PRENOM,datedenaissance,adresse,email,dispo,num);
    bool test=V1.update();

    if(test)
    {
     QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Modification effectué\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tab_volontaire->setModel(V.afficher());
     ui->comboBox_2->clear();
     ui->comboBox_2->addItems(V.lister());
     ui->comboBox_3->clear();
     ui->comboBox_3->addItems(V.lister());
     ui->comboBox_4->clear();
     ui->comboBox_4->addItems(V.lister());
     ui->comboBox_5->clear();
     ui->comboBox_5->addItems(V.listerEmail());
    }
    else
    {
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
             QObject::tr("Modification erronée\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }

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

    ui->le_nom_3->setText(nom);
    ui->le_prenom_3->setText(prenom);
    ui->le_date_3->setDate(datedenaissance);
    ui->le_adresse_3->setText(adresse);
    ui->le_email_3->setText(email);
    ui->cb_dispo_6->setCurrentText(dispo);
    ui->le_num_6->setText(num);

}

void MainWindow::on_le_rech_2_textChanged()
{
    V.clearTable(ui->tab_volontaire);
    QString rech=ui->le_rech_2->text();
    ui->tab_volontaire->setModel(V.rechercher(rech));
}



//Refresh Buttons
void MainWindow::on_pushButton_clicked()
{
    ui->tab_volontaire->setModel(V.afficher());
    ui->comboBox_2->clear();
    ui->comboBox_2->addItems(V.lister());
    ui->comboBox_3->clear();
    ui->comboBox_3->addItems(V.lister());
    ui->comboBox_4->clear();
    ui->comboBox_4->addItems(V.lister());
    ui->comboBox_5->clear();
    ui->comboBox_5->addItems(V.listerEmail());
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tab_volontaire->setModel(V.afficher());
    ui->comboBox_2->clear();
    ui->comboBox_2->addItems(V.lister());
    ui->comboBox_3->clear();
    ui->comboBox_3->addItems(V.lister());
    ui->comboBox_4->clear();
    ui->comboBox_4->addItems(V.lister());
    ui->comboBox_5->clear();
    ui->comboBox_5->addItems(V.listerEmail());
    ui->le_rech->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tab_volontaire->setModel(V.afficher());
    ui->comboBox_2->clear();
    ui->comboBox_2->addItems(V.lister());
    ui->comboBox_3->clear();
    ui->comboBox_3->addItems(V.lister());
    ui->comboBox_4->clear();
    ui->comboBox_4->addItems(V.lister());
    ui->comboBox_5->clear();
    ui->comboBox_5->addItems(V.listerEmail());
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
printer.setOutputFileName("C:/Users/User/OneDrive/Bureau/Integration/Final0/PDFV/listeDesVolontaires.pdf");

QTextDocument doc;
doc.setHtml(strStream);
doc.print(&printer);
            QMessageBox::information(nullptr, QObject::tr("Sauvegardement du PDF "),
                                              QObject::tr("pdf enregistré.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}


int MainWindow::on_pb_cf_clicked()
{
   QString id= ui->comboBox_4->currentText();
   QString nom= ui->lineEdit_2->text();
   QString prenom= ui->lineEdit_3->text();
   QString points= ui->lineEdit_4->text();
   QPrinter printer;

   printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setOutputFileName("C:/Users/User/OneDrive/Bureau/Integration/Final0/carteF/carte("+id+").pdf");
   QPainter painter;
   QImage carte("C:/Users/User/OneDrive/Bureau/Integration/Final0/carte.png");
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
          painter.end();
          QMessageBox::information(nullptr, QObject::tr("Sauvegardement du PDF "),
                                     QObject::tr("carte imprimé sur carte Fidélité .\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
          return 0;
}

void MainWindow::on_comboBox_4_currentTextChanged(const QString &arg1)
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


        smtp->sendMail(ui->le_mail->text(), ui->comboBox_5->currentText() , ui->le_objet->text(),ui->te_message->toPlainText());

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
        slice->setPen(QPen());
        slice->setBrush(QColor(255, 0, 255));
        }
    if ( dispo!=0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
        slice1->setBrush(QColor(0, 255, 255));
    }

    QChart *chart = new QChart();
    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle("disponibilité des volontaires :Nb Volontaires: "+ QString::number(total));
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);

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
    chart->setAnimationOptions(QChart::AllAnimations);

    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}

void MainWindow::arduino_init()
{
    serial->setPortName(portname);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
    if (SIGNAL(readyRead()))
        qDebug()<<"test";
    connect(serial,SIGNAL(readyRead()),this,SLOT(serial_read()));
}




void MainWindow::serial_read()
{
    if(serial->isReadable()&&arduino_available)
    {

     serialData = serial->readAll();
     serialBuffer +=QString::fromStdString(serialData.toStdString());
    MainWindow::update_dist(serialBuffer);
/*
    if(tem){
        QSqlQuery query;
        temperature=serialBuffer.mid(2,4);
        query.prepare("INSERT INTO TEMP (TEMP) " "VALUES (:temperature)");
        query.bindValue(0,temperature);
        query.exec();
        test=temperature;
        qDebug()<<temperature+"b";
        qDebug()<<test+"a";
        tem=false;
    }
    if(test!=temperature){
      tem=true;
    }

    }
    */
}
}

void MainWindow::update_dist(const QString sensor_reading)
{
    ui->lcdNumber->display(sensor_reading);

}

void MainWindow::on_radioButton_clicked()
{
    if(serial->isWritable()){
            serial->write("1");
            qDebug()<<"Debut";
        }
}


void MainWindow::on_radioButton_2_clicked()
{
    if(serial->isWritable()){
            serial->write("4");
            qDebug()<<"Fin";
        }
}

//******************* Tamim *******************

void MainWindow::on_tpushButtonAjouter_4_clicked()
{
    QString CINP=ui->lineEditCINP_7->text();
    QString NOMP=ui->lineEditNOMP_7->text();
    QString PRENOMP=ui->lineEditPRENOMP_7->text();
    QDate DATE_NAISSANCEP=ui->dateEdit_7->date();
    QString ADRESSEP=ui->lineEditADRESSEP_7->text();
    QString ETATP=ui->lineEditETATP_7->text();
    QString AGEP=ui->lineEditAGEP_7->text();
    Patient P(CINP,NOMP,PRENOMP,DATE_NAISSANCEP,ADRESSEP,ETATP,AGEP);
    bool test=P.ajouter();
    if(test)
        {

        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Ajout effectué\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_4->setModel(P.afficher());
        }
        else
    {
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"), QObject::tr("Ajout non effectué\n""Click Cancel to exit."), QMessageBox::Cancel);

    }
}


void MainWindow::on_tpushButtonSUPP_4_clicked()
{
    Patient P1 ;
    P1.setCINP(ui->lineEditSUPP_4->text());
    bool test=P1.supprimer(P1.getCINP());
    if(test)
        {
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("suppression  effectué\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView_4->setModel(P.afficher());
        }
        else
    {
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"), QObject::tr("suppression non effectué\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_tpushButtonModifier_4_clicked()
{
    QString CINP=ui->lineEditCINP_8->text();
    QString NOMP=ui->lineEditNOMP_8->text();
    QString PRENOMP=ui->lineEditPRENOMP_8->text();
    QDate DATE_NAISSANCEP=ui->dateEdit_8->date();
    QString ADRESSEP=ui->lineEditADRESSEP_8->text();
    QString ETATP=ui->lineEditETATP_8->text();
    QString AGEP=ui->lineEditAGEP_8->text();

    Patient P2(CINP,NOMP,PRENOMP,DATE_NAISSANCEP,ADRESSEP,ETATP,AGEP);
    bool test=P2.update();

    if(test)
    {
     QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Modification effectué\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tableView_4->setModel(P.afficher());
    }
    else
    {
     QMessageBox::critical(nullptr, QObject::tr("Not OK"),
             QObject::tr("Modification erronée\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_tpb_triparid_4_clicked()
{
    Patient E ;
        ui->tableView_4->setModel(E.trierpatient1());
}

void MainWindow::on_tpb_triparnom_4_clicked()
{
    Patient E ;
        ui->tableView_4->setModel(E.trierpatient2());
}

void MainWindow::on_tpushButtonRECHERCHE_10_clicked()
{
    Patient E ;
         QString rech =ui->lineEditRECHERCHE_10->text();
         if (rech=="")

             ui->tableView_4->setModel(E.afficher());
         else
             ui->tableView_4->setModel(E.recherche(rech));
}

void MainWindow::on_tpushButton_4_clicked()
{
    QString strStream;
        strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
            if (QFileInfo(strStream).suffix().isEmpty()) { strStream.append(".pdf"); }

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
           // printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(strStream);



                  QTextStream out(&strStream);

                  const int rowCount = ui->tableView_4->model()->rowCount();
                  const int columnCount = ui->tableView_4->model()->columnCount();
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
                      if (!ui->tableView_4->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tableView_4->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->tableView_4->isColumnHidden(column)) {
                              QString data =ui->tableView_4->model()->data(ui->tableView_4->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_tpushButtonSTAT_4_clicked()
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

void MainWindow::on_tpushButtonRECHERCHE_11_clicked()
{
    Patient E ;
         QString rech =ui->lineEditRECHERCHE_11->text();
         if (rech=="")

             ui->tableView_4->setModel(E.afficher());
         else
             ui->tableView_4->setModel(E.recherche3(rech));
}

void MainWindow::on_tpushButtonRECHERCHE_12_clicked()
{
    Patient E ;
         QString rech =ui->lineEditRECHERCHE_12->text();
         if (rech=="")

             ui->tableView_4->setModel(E.afficher());
         else
             ui->tableView_4->setModel(E.recherche2(rech));
}



void MainWindow::on_tpb_triparprenom_4_clicked()
{
    Patient E ;
        ui->tableView_4->setModel(E.trierpatient3());
}

void MainWindow::on_radioButton_30_toggled( )
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/User/OneDrive/Bureau/Integration/Final0/QTDark.stylesheet")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_27_toggled( )
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/User/OneDrive/Bureau/Integration/Final0/Adaptic.qss")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_29_toggled( )
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/User/OneDrive/Bureau/Integration/Final0/Perstfic.qss")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_28_toggled( )
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/User/OneDrive/Bureau/Integration/Final0/Fibers.qss")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_31_toggled( )
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_33_toggled( )
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/User/OneDrive/Bureau/Integration/Final0/Wstartpage.qss")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_32_toggled()
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/User/OneDrive/Bureau/Integration/Final0/VisualScript.qss")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

void MainWindow::on_radioButton_34_toggled()
{
    QList<QWidget *> widgets = this->findChildren<QWidget *>();

      QFile styleSheetFile("C:/Users/User/OneDrive/Bureau/Integration/Final0/Diplaytap.qss")    ;
      styleSheetFile.open(QFile::ReadOnly) ;
      QString styleSheet = QLatin1String(styleSheetFile.readAll())  ;
      widgets.at(0)->setStyleSheet(styleSheet);
}

  //******************* Larbi *******************

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
       // printer.setPaperSize(QPrinter::A4);
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
                    +"<div style=\"text-align: center;\"><img src=C:/Users/User/OneDrive/Bureau/Integration/Final0/inf2.png /></div>"
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
        ui->tabWidget_2->setTabText(0,"Add event");
        ui->tabWidget_2->setTabText(1,"View event");
        ui->tabWidget_2->setTabText(2,"Update event");


        ui->label_79->setText("ID event");
        ui->label_82->setText("Name event");
        ui->label_83->setText("Type event");
        ui->label_78->setText("location event");
        ui->label_81->setText("Start date");
        ui->label_80->setText("End date");
        ui->pb_modifierevent->setText("Edit");
        ui->pb_ajouterevent->setText("Add");
        ui->pb_triparidevent->setText("Sort by id");
        ui->pb_triparnomevent->setText("Sort by name");
        ui->le_supprimer->setText("Delete");
        ui->pb_changer->setText("Change");
        ui->label_87->setText("ID event");
        ui->label_88->setText("Name event");
        ui->label_90->setText("Type event");
        ui->label_91->setText("Location event");
        ui->label_89->setText("Start date");
        ui->label_92->setText("End date");
        ui->label_19->setText("Add Event");
        ui->label_20->setText("Update Event");
        ui->pb_kouss->setText("Employees");
        ui->pb_amine->setText("Voluntary");

        ui->pb_sarr->setText("Stock");
        ui->pb_larbi->setText("Events");
        ui->label_85->setText("Add Event");
        ui->label_94->setText("Update Event");
    }
    else if (ui->comboBoxevent->currentText()=="FR")
    {
        ui->tabWidget_2->setTabText(0,"Ajouter evenement");
        ui->tabWidget_2->setTabText(1,"Afficher evenement");
        ui->tabWidget_2->setTabText(2,"Modifier evenement");

        ui->label_79->setText("ID evenement");
        ui->label_82->setText("Nom evenement");
        ui->label_83->setText("Type evenement");
        ui->label_78->setText("Lieu evenement");
        ui->label_81->setText("date debut");
        ui->label_80->setText("date fin");
        ui->pb_modifierevent->setText("modifier");
        ui->pb_ajouterevent->setText("Ajouter");
        ui->pb_triparidevent->setText("tri par id");
        ui->pb_triparnomevent->setText("tri par nom");
        ui->le_supprimer->setText("supprimer");
        ui->pb_changer->setText("changer");
        ui->label_87->setText("ID evenement");
        ui->label_88->setText("Nom evenement");
        ui->label_90->setText("Type evenement");
        ui->label_91->setText("Lieu evenement");
        ui->label_89->setText("Date debut");
         ui->label_92->setText("Date fin");
        ui->pb_kouss->setText("Employés");
        ui->pb_amine->setText("Volontaire");

        ui->pb_sarr->setText("Produit");
        ui->pb_larbi->setText("Evenements");
        ui->label_85->setText("Ajouter un evenement");
        ui->label_94->setText("Modifier un evenement");





    }

}

void MainWindow::on_tabWidget_2_currentChanged()
{
    E.statistique(ui->statis);
}


void MainWindow::on_tabWidget_2_tabBarClicked()
{
    E.statistique(ui->statis);
}
////////////////////////////////////// signup///////////////////////////////////////////
void MainWindow::on_signup_clicked()
{
    QString signup_cin=ui->signup_cin->text();
    QString signup_username=ui->signup_username->text();
    QString signup_password=ui->signup_password->text();
    QString signup_adress=ui->signup_adress->text();
    QString signup_email=ui->signup_email->text();
    QString signup_role=ui->cb_role->currentText();

    QSqlQuery qry;
    qry.prepare("INSERT INTO employe(cin,nom,adresse,email,role,password)"
                "VALUES (:cin,:nom,:adresse,:email,:role,:password)");
    qry.bindValue(":cin",signup_cin);
    qry.bindValue(":nom",signup_username);
    qry.bindValue(":adresse",signup_adress);
    qry.bindValue(":email",signup_email);
    qry.bindValue(":password",signup_password);
    qry.bindValue(":role",signup_role);
    if(qry.exec())
    {
        QMessageBox::information(this,"Inserted","Data inserted successfully");
    }else {
        QMessageBox::information(this,"Not inserted","Data is not insrted");
    }

}

/////////////////////////////////////login//////////////////////////////////
void MainWindow::on_login_clicked()
{

    QString val=ui->login_password->text();
    QString val1=ui->login_cin->text();
    QSqlQuery qry;
    qry.prepare("select * from employe where cin='"+val1+"' AND password='"+val+"'");
    if(qry.exec())
    {
    while(qry.next())
    {

        QString rolefromdb=qry.value(10).toString();
        if(rolefromdb=="admin")
        {
            QMessageBox::information(this,"Success","Login Admin success");
             ui->STW->setCurrentIndex(2);
             ui->pb_sarr->setVisible(true);
              ui->pb_tamim->setVisible(true);
              ui->pb_larbi->setVisible(true);
              ui->pb_amine->setVisible(true);
             ui-> pb_kouss->setVisible(true);
             ui-> logout->setVisible(true);
             ui->logosmart->setVisible(true);
             ui->sac->setVisible(true);
             t=false;
        }else if(rolefromdb=="RH")
        {
            ui->STW->setCurrentIndex(2);
            ui->pb_sarr->setVisible(false);
             ui->pb_tamim->setVisible(false);
             ui->pb_larbi->setVisible(false);
             ui->pb_amine->setVisible(false);
            ui-> pb_kouss->setVisible(false);
            ui-> logout->setVisible(true);
            ui->logosmart->setVisible(true);
            ui->sac->setVisible(true);
            t=false;
        }else if(rolefromdb=="responsable stock")
        {
            ui->STW->setCurrentIndex(5);
            ui->pb_sarr->setVisible(false);
             ui->pb_tamim->setVisible(false);
             ui->pb_larbi->setVisible(false);
             ui->pb_amine->setVisible(false);
            ui-> pb_kouss->setVisible(false);
            ui-> logout->setVisible(true);
            ui->logosmart->setVisible(true);
            ui->sac->setVisible(true);
            t=false;
        }else if(rolefromdb=="responsable event")
        {
            ui->STW->setCurrentIndex(6);
            ui->pb_sarr->setVisible(false);
             ui->pb_tamim->setVisible(false);
             ui->pb_larbi->setVisible(false);
             ui->pb_amine->setVisible(false);
            ui-> pb_kouss->setVisible(false);
            ui-> logout->setVisible(true);
            ui->logosmart->setVisible(true);
            ui->sac->setVisible(true);
            t=false;
        }else if(rolefromdb=="responsable volontaire")
        {
            ui->STW->setCurrentIndex(3);
            ui->pb_sarr->setVisible(false);
             ui->pb_tamim->setVisible(false);
             ui->pb_larbi->setVisible(false);
             ui->pb_amine->setVisible(false);
            ui-> pb_kouss->setVisible(false);
            ui-> logout->setVisible(true);
            ui->logosmart->setVisible(true);
            ui->sac->setVisible(true);
            t=false;

        }
        else if(rolefromdb=="" or val1!=qry.value(1).toString() or t)
        {
            QMessageBox::information(this,"Failed","Login failed");
        }


    }
    }



}


void MainWindow::on_acc_clicked()
{
    ui->STW->setCurrentIndex(0);
}


void MainWindow::on_returnlogin_clicked()
{
     ui->STW->setCurrentIndex(1);
      ui->logout->setVisible(false);
}


void MainWindow::on_logout_clicked()
{
    ui->STW->setCurrentIndex(1);
    ui->pb_sarr->setVisible(false);
     ui->pb_tamim->setVisible(false);
     ui->pb_larbi->setVisible(false);
     ui->pb_amine->setVisible(false);
    ui-> pb_kouss->setVisible(false);
     ui->logout->setVisible(false);
     ui->logosmart->setVisible(false);
     ui->sac->setVisible(false);

}


/*******************************************************Sarra****************************************************************/


void MainWindow::on_ajouterp_5_clicked()
{



    QString id=ui->le_idpr_5->text();
    QString nom=ui->le_nompr_5->text();
    QString genre=ui->le_genrepr_5->text();
    int quantite=ui->la_qtepr_5->text().toInt();
    int poids=ui->le_poidspr_5->text().toInt();
    int taille=ui->la_taillepr_5->text().toInt();
    QDate datep= ui->la_datepr_5->date();


    QString idh=ui->le_idpr_5->text();




   stock S(id,nom,quantite,poids,taille,genre,datep);
    bool test= S.ajouter();



    if(test )
    {
        //actualiser
        ui->tab_stock_5->setModel(S.afficher());

        historique h( "ajout", idh);

                    h.ajouter_historique();
                    ui->tab_hispr_5->setModel(H.afficherHistorique());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("Ajout effectué\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tri_alphabetique_stockpr_5_clicked()
{
    ui->tab_stock_5->setModel(S.afficher_tri_alphabetique_Stock());

}

void MainWindow::on_tri_desc_idpr_5_clicked()
{
    ui->tab_stock_5->setModel(S.afficher_tri_descendant_Stock());

}

void MainWindow::on_tri_asc_idpr_5_clicked()
{
ui->tab_stock_5->setModel(S.afficher_tri_identifiant_Stock());
}

void MainWindow::on_pb_supppr_5_clicked()
{
   // QSqlQuery query;

    S.setid(ui->le_id_supppr_5->text());

    QString idh=ui->le_id_supppr_5->text();


    bool test=S.supprimer(S.getid());

    if(test)
    {



        ui->tab_stock_5->setModel(S.afficher());



        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                //notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION STOCK ","La suppression du produit est effectuée",QSystemTrayIcon::Information,15000);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("supp effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

        historique h("suppression",idh);
        h.ajouter_historique();
        ui->tab_hispr_5->setModel(H.afficherHistorique());
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                  QObject::tr("error::"), QMessageBox::Cancel);


}

void MainWindow::on_pb_modifierpr_5_clicked()
{
            S.setid(ui->id_modpr_5->text());
            S.setnom(ui->nom_modpr_5->text());
            S.setqte(ui->qte_modpr_5->text().toInt());
            S.setdate(ui->date_modpr_5->date());
            S.setgenre(ui->genre_modpr_5->text());
            S.setpoids(ui->poids_modpr_5->text().toInt());
            S.settaille(ui->taille_modpr_5->text().toInt());



            QString idh=ui->id_modpr_5->text();




            if(S.modifier())
            {


                historique h( "modification", idh);
                h.ajouter_historique();
                ui->tab_hispr_5->setModel(H.afficherHistorique());

                ui->tab_stock_5->setModel(S.afficher());

                 QMessageBox::information(nullptr, QObject::tr("modification produit"),
                                          QObject::tr("modification avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
                ui->id_modpr_5->clear();
                ui->nom_modpr_5->clear();
                ui->qte_modpr_5->clear();
                ui->poids_modpr_5->clear();
                ui->taille_modpr_5->clear();
                ui->date_modpr_5->clear();
                ui->genre_modpr_5->clear();





            }
            else
                QMessageBox::critical(nullptr, QObject::tr("modification produit"),
                                         QObject::tr("modification échouée.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_recherche_Stockpr_5_clicked()
{



    ui->tab_stock_5->setModel(S.recherche_date(ui->datepr_5->date()));


        /* QDate datep=ui->input_rech->text().date();
               QDate datep=ui->date;
               ui->tab_stock->setModel(S.recherche_date(datep));*/
               QMessageBox::information(nullptr,QObject::tr("OK"),
                                         QObject::tr("recherche effectue.\n"
                                                     "clic cancel to exit."),QMessageBox::Cancel);


}

void MainWindow::on_Pdfpr_5_clicked()
{
    QPdfWriter pdf("C:/Users/User/OneDrive/Bureau/Integration/Final0/PDF/sarra.pdf");
    QPainter painter(&pdf);
   int i = 4000;
        painter.setPen(Qt::red);
        painter.setFont(QFont("Comic Sans MS", 30));
        painter.drawText(1100,1100,"Liste Des Produits ");
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Comic Sans MS", 50));
        painter.drawRect(100,100,7300,1900);
        painter.setPen(Qt::blue);
        painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/Users/User/OneDrive/Bureau/Integration/Final0/inf.png"));
        painter.drawRect(0,3000,9600,500);
        painter.setPen(Qt::blue);

        painter.setFont(QFont("Comic Sans MS", 15));
        painter.drawText(200,3300,"Identifiant");
        painter.drawText(1750,3300,"Nom");
        painter.drawText(2400,3300,"Quantite");
        painter.drawText(3800,3300,"Poids");
        painter.drawText(4600,3300,"Taille");
        painter.drawText(5400,3300,"Genre");
        painter.drawText(7400,3300,"Date");




        QSqlQuery query;
        query.prepare("select * from stock");
        query.exec();
        while (query.next())
        {
            painter.setPen(Qt::red);
            painter.drawText(500,i,query.value(0).toString());
            painter.setPen(Qt::black);
            painter.drawText(1800,i,query.value(1).toString());
            painter.drawText(2900,i,query.value(2).toString());
            painter.drawText(4000,i,query.value(3).toString());
            painter.drawText(4800,i,query.value(4).toString());
            painter.drawText(5600,i,query.value(5).toString());
            painter.drawText(6600,i,query.value(6).toString());

            painter.setPen(Qt::blue);




           i = i + 500;
        }
        int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/User/OneDrive/Bureau/Integration/Final0/PDF/sarra.pdf"));
                painter.end();
            }
            if (reponse == QMessageBox::No)
            {
                 painter.end();
            }
}

void MainWindow::on_statpr_5_clicked()
{



    QSqlQueryModel * model= new QSqlQueryModel();
                               model->setQuery("select * from stock where quantite BETWEEN '0' AND '99' ");
                               float e=model->rowCount();
                               model->setQuery("select * from stock  where quantite BETWEEN '100' AND '200' ");
                               float ee=model->rowCount();
                               model->setQuery("select * from stock where quantite BETWEEN '201' AND '300' ");
                               float eee=model->rowCount();
                               float total=e+ee+eee;
                               QString a=QString("0-99:  "+ QString::number((e*100)/total,'f',2)+"%" );
                               QString b=QString("100-200:  "+QString::number((ee*100)/total,'f',2)+"%" );
                               QString c=QString("201-300:   "+QString::number((eee*100)/total,'f',2)+"%" );
                               QPieSeries *series = new QPieSeries();
                               series->append(a,e);
                               series->append(b,ee);
                               series->append(c,eee);
                       if (e!=0)
                       {QPieSlice *slice = series->slices().at(0);
                        slice->setLabelVisible();
                        slice->setPen(QPen());}
                       if ( ee!=0)
                       {
                                // Add label, explode and define brush for 2nd slice
                                QPieSlice *slice1 = series->slices().at(1);
                                //slice1->setExploded();
                                slice1->setLabelVisible();
                       }
                       if(eee!=0)
                       {
                                // Add labels to rest of slices
                                QPieSlice *slice2 = series->slices().at(2);
                                //slice1->setExploded();
                                slice2->setLabelVisible();
                       }
                               // Create the chart widget
                               QChart *chart = new QChart();
                               // Add data to chart with title and hide legend
                               chart->addSeries(series);
                               chart->setTitle("Pourcentage des quantites produits : nombre des produits: "+ QString::number(total));
                               chart->legend()->hide();
                               // Used to display the chart
                               QChartView *chartView = new QChartView(chart);
                               chartView->setRenderHint(QPainter::Antialiasing);
                               chartView->resize(1000,500);
                               chartView->show();

}






void MainWindow::on_qrCodepr_5_clicked()
{
    int tabeq=ui->tab_stock_5->currentIndex().row(); //track selected item
               QVariant idd=ui->tab_stock_5->model()->data(ui->tab_stock_5->model()->index(tabeq,0));
               QString id=idd.toString();
              // QString code=idd.toSTring();
               QSqlQuery qry;
               qry.prepare("select * from Stock where id=:id");
               qry.bindValue(":id",id);
               qry.exec();

                QString nom,genre;//attributs
                int quantite,poids,taille;
                QDate datep;

              while(qry.next()){

                  id=qry.value(1).toString();
                   nom=qry.value(2).toString();
                    quantite=qry.value(3).toInt();
                   poids=qry.value(4).toInt();
                   taille=qry.value(5).toInt();
                   genre=qry.value(6).toString();
                   datep=qry.value(7).toDate();


               }
               id=QString(id);
                      id="id:\t" +id+ "NOM\t:" +nom+ "quantite:\t" +quantite+ "poids:\t" +poids+ "stock:\t" +taille+ "genre:\t" +genre ;
               QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

               // Read the black & white pixels
               QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
               for (int y = 0; y < qr.getSize(); y++) {
                   for (int x = 0; x < qr.getSize(); x++) {
                       int color = qr.getModule(x, y);  // 0 for white, 1 for black

                       // You need to modify this part
                       if(color==0)
                           im.setPixel(x, y,qRgb(254, 254, 254));
                       else
                           im.setPixel(x, y,qRgb(0, 0, 0));
                   }
               }
               im=im.scaled(200,200);
              ui->qr_code_5->setPixmap(QPixmap::fromImage(im));
}


void MainWindow::NumPressed(){

    // Sender returns a pointer to the button pressed
    QPushButton *button = (QPushButton *)sender();

    // Get number on button
    QString butVal = button->text();

    // Get the value in the display
    QString displayVal = ui->Display_5->text();

    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){

        // calcVal = butVal.toDouble();
        ui->Display_5->setText(butVal);

    } else {
        // Put the new number to the right of whats there
        QString newVal = displayVal + butVal;

        // Double version of number
        double dblNewVal = newVal.toDouble();

        // calcVal = newVal.toDouble();

        // Set value in display and allow up to 16
        // digits before using exponents
        ui->Display_5->setText(QString::number(dblNewVal, 'g', 16));

    }
}

void MainWindow::MathButtonPressed(){

    // Cancel out previous math button clicks
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    // Store current value in Display
    QString displayVal = ui->Display_5->text();
    calcVal = displayVal.toDouble();

    // Sender returns a pointer to the button pressed
    QPushButton *button = (QPushButton *)sender();

    // Get math symbol on the button
    QString butVal = button->text();

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else {
        subTrigger = true;
    }

    // Clear display
    ui->Display_5->setText("");

}

void MainWindow::EqualButtonPressed(){

    // Holds new calculation
    double solution = 0.0;

    // Get value in display
    QString displayVal = ui->Display_5->text();
    double dblDisplayVal = displayVal.toDouble();

    // Make sure a math button was pressed
    if(addTrigger || subTrigger || multTrigger || divTrigger ){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        } else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        } else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        } else {
            solution = calcVal / dblDisplayVal;
        }
    }

    // Put solution in display
    ui->Display_5->setText(QString::number(solution));






    if(solution > 100000 )
    {


                    QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                          QObject::tr("Quantité Dépassée\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }


}

void MainWindow::ChangeNumberSign(){

    // Get the value in the display
    QString displayVal = ui->Display_5->text();

    // Regular expression checks if it is a number
    // plus sign
    QRegExp reg("[-+]?[0-9.]*");

    // If it is a number change the sign
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        // Put solution in display
        ui->Display_5->setText(QString::number(dblDisplayValSign));

    }


}









void MainWindow::on_rech_nompr_5_clicked()
{
    ui->tab_stock_5->setModel(S.recherche_nom(ui->input_rechpr_5->text()));

    // ui->tab_stock->setModel(S.recherche_date(ui->date->date()));


         /* QDate datep=ui->input_rech->text().date();
                QDate datep=ui->date;
                ui->tab_stock->setModel(S.recherche_date(datep));*/
                QMessageBox::information(nullptr,QObject::tr("OK"),
                                          QObject::tr("recherche effectue.\n"
                                                      "clic cancel to exit."),QMessageBox::Cancel);

}



void MainWindow::update_label()
{
    data=A.read_from_arduino();
    QString idt=ui->idt->text();

        if(data=="3")

        ui->tabaff->setModel(e.afficher(idt));





        else
        {if (data=="2"){

        ui->label_259->setText("FONCTIONNEMENT");}
        else

      ui->label_259->setText("NON DETECTION");}
}

void MainWindow::on_verifier_clicked()   // implémentation du slot bouton on
{
     A.write_to_arduino("3"); //envoyer 1 à arduino
}




void MainWindow::on_pushButton55_clicked()   // implémentation du slot bouton on
{
     A.write_to_arduino("2");

}

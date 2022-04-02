#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "employe.h"
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
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mSocket=new QTcpSocket(this);
    connect(mSocket,&QTcpSocket::readyRead,[&](){
        QTextStream T(mSocket);
        auto text = T.readAll();
        ui->textEdit->append(text);
    });
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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    int cin=ui->le_cin->text().toInt();
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

    int cin =ui->le_id_supp->text().toInt();
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



void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}

void MainWindow::on_quitter_clicked()
{
    this->close();
}


void MainWindow::on_pushButton_clicked()
{
    int cin=ui->le_mod_cin->text().toInt();
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
        QPdfWriter pdf("C:/Users/kossay/Desktop/qt/Employe/PDF/fiche.pdf");
        QPainter painter(&pdf);
       int i = 6700;
            painter.setPen(Qt::red);
            painter.setFont(QFont("MS Shell Dlg 2", 30));
            painter.drawText(3300,1100,"Fiche de paie ");
            painter.setPen(Qt::blue);
            painter.setFont(QFont("Comic Sans MS", 50));
            //painter.drawRect(1000,50,7300,1900);
            painter.setPen(Qt::black);
            painter.drawPixmap(QRect(4200,70,2600,2200),QPixmap("‪C:/Users/kossay/Desktop/qt/Employe/inf.png"));
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
            painter.drawText(2900,7800,"Salaire brut: ");
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
                    QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/kossay/Desktop/qt/Employe/PDF/fiche.pdf"));
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


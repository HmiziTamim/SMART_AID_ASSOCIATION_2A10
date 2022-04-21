#include <QMessageBox>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "stock.h"
#include <QSqlQuery>
#include <QIntValidator> //ensures a string contains a valid integer within a specified range
#include <QSqlError>
#include<QSystemTrayIcon>
#include <QRegExp>
#include "connection.h"
#include "historique.h"
#include "histomod.h"
#include <QFileDialog>
#include <QPainter>
#include <QPdfWriter>  //generate PDFs that can be used as a paint device
#include <QDesktopServices> //accessing common desktop services
#include "qrcode.h"
#include <QPixmap>

#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>  //display charts

#include <QtCharts/QLegend>  //displays the legend of a chart
  //data in line charts
#include <QtCharts/QCategoryAxis>  //places named ranges on the axis
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
//#include <QUrl>


QT_CHARTS_USE_NAMESPACE


double calcVal = 0.0;

// Will define if this was the last math button clicked
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;



using namespace qrcodegen;
using namespace std;

MainWindow::MainWindow(QWidget *parent) : //Constructeur de la classe mainwindow généré automatiquement
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->le_id->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
    ui->la_qte->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
    ui->le_poids->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
    ui->la_taille->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
    ui->le_nom->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z]{7}")));
    ui->le_genre->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z]{6}")));

    ui->le_id_supp->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));

    ui->id_mod->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
    ui->qte_mod->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
    ui->poids_mod->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
    ui->taille_mod->setValidator(new QRegExpValidator(QRegExp("[0-9]{5}")));
    ui->nom_mod->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z]{7}")));
    ui->genre_mod->setValidator(new QRegExpValidator(QRegExp("[a-z-A-Z]{6}")));




    ui->le_id->setPlaceholderText("Entrez le id...");
    ui->le_nom->setPlaceholderText("Entrez le nom...");
    ui->le_genre->setPlaceholderText("Entrez le genre...");
    ui->la_qte->setPlaceholderText("Entrez la quantite...");
    ui->le_poids->setPlaceholderText("Entrez le poids...");
    ui->la_taille->setPlaceholderText("Entrez la taille...");

    ui->le_id_supp->setPlaceholderText("Entrez le id à supprimer...");

    ui->id_mod->setPlaceholderText("Entrez le id...");
    ui->nom_mod->setPlaceholderText("Entrez le nom...");
    ui->genre_mod->setPlaceholderText("Entrez le genre...");
    ui->qte_mod->setPlaceholderText("Entrez la quantite...");
    ui->poids_mod->setPlaceholderText("Entrez le poids...");
    ui->taille_mod->setPlaceholderText("Entrez la taille...");




    ui->tab_stock->setModel(S.afficher());
  ui->tab_his->setModel(H.afficherHistorique());


    ui->Display->setText(QString::number(calcVal));

        // Will hold references to all the number buttons
        QPushButton *numButtons[10];

        // Cycle through locating the buttons
        for(int i = 0; i < 10; ++i){
            QString butName = "Button" + QString::number(i);

            // Get the buttons by name and add to array
            numButtons[i] = MainWindow::findChild<QPushButton *>(butName);

            // When the button is released call num_pressed()
            connect(numButtons[i], SIGNAL(released()), this,
                    SLOT(NumPressed()));
        }

        // Connect signals and slots for math buttons
        connect(ui->Add, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
        connect(ui->Subtract, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
        connect(ui->Multiply, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));
        connect(ui->Divide, SIGNAL(released()), this,
                SLOT(MathButtonPressed()));

        // Connect equals button
        connect(ui->Equals, SIGNAL(released()), this,
                SLOT(EqualButtonPressed()));

        // Connect change sign
        connect(ui->ChangeSign, SIGNAL(released()), this,
                SLOT(ChangeNumberSign()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{



    QString id=ui->le_id->text();
    QString nom=ui->le_nom->text();
    QString genre=ui->le_genre->text();
    int quantite=ui->la_qte->text().toInt();
    int poids=ui->le_poids->text().toInt();
    int taille=ui->la_taille->text().toInt();
    QDate datep= ui->la_date->date();


    QString idh=ui->le_id->text();




   stock S(id,nom,quantite,poids,taille,genre,datep);
    bool test= S.ajouter();



    if(test )
    {
        //actualiser
        ui->tab_stock->setModel(S.afficher());

        historique h( "ajout", idh);

                    h.ajouter_historique();
                    ui->tab_his->setModel(H.afficherHistorique());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("Ajout effectué\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tri_alphabetique_stock_clicked()
{
    ui->tab_stock->setModel(S.afficher_tri_alphabetique_Stock());

}

void MainWindow::on_tri_desc_id_clicked()
{
    ui->tab_stock->setModel(S.afficher_tri_descendant_Stock());

}

void MainWindow::on_tri_asc_id_clicked()
{
ui->tab_stock->setModel(S.afficher_tri_identifiant_Stock());
}

void MainWindow::on_pb_supp_clicked()
{
    QSqlQuery query;

    S.setid(ui->le_id_supp->text());

    QString idh=ui->le_id_supp->text();


    bool test=S.supprimer(S.getid());

    if(test)
    {



        ui->tab_stock->setModel(S.afficher());



        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                //notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION STOCK ","La suppression du produit est effectuée",QSystemTrayIcon::Information,15000);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("supp effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

        historique h("suppression",idh);
        h.ajouter_historique();
        ui->tab_his->setModel(H.afficherHistorique());
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                  QObject::tr("error::"), QMessageBox::Cancel);


}

void MainWindow::on_pb_modifier_clicked()
{
            S.setid(ui->id_mod->text());
            S.setnom(ui->nom_mod->text());
            S.setqte(ui->qte_mod->text().toInt());
            S.setdate(ui->date_mod->date());
            S.setgenre(ui->genre_mod->text());
            S.setpoids(ui->poids_mod->text().toInt());
            S.settaille(ui->taille_mod->text().toInt());



            QString idh=ui->id_mod->text();




            if(S.modifier())
            {


                historique h( "modification", idh);
                h.ajouter_historique();
                ui->tab_his->setModel(H.afficherHistorique());

                ui->tab_stock->setModel(S.afficher());

                 QMessageBox::information(nullptr, QObject::tr("modification produit"),
                                          QObject::tr("modification avec succès.\n""Click Cancel to exit."), QMessageBox::Cancel);
                ui->id_mod->clear();
                ui->nom_mod->clear();
                ui->qte_mod->clear();
                ui->poids_mod->clear();
                ui->taille_mod->clear();
                ui->date_mod->clear();
                ui->genre_mod->clear();





            }
            else
                QMessageBox::critical(nullptr, QObject::tr("modification produit"),
                                         QObject::tr("modification échouée.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_recherche_Stock_clicked()
{



    ui->tab_stock->setModel(S.recherche_date(ui->date->date()));


        /* QDate datep=ui->input_rech->text().date();
               QDate datep=ui->date;
               ui->tab_stock->setModel(S.recherche_date(datep));*/
               QMessageBox::information(nullptr,QObject::tr("OK"),
                                         QObject::tr("recherche effectue.\n"
                                                     "clic cancel to exit."),QMessageBox::Cancel);


}

void MainWindow::on_Pdf_clicked()
{
    QPdfWriter pdf("C:/Users/sarra/Desktop/Gestion_Stock/PDF/sarra.pdf");
    QPainter painter(&pdf);
   int i = 4000;
        painter.setPen(Qt::red);
        painter.setFont(QFont("Comic Sans MS", 30));
        painter.drawText(1100,1100,"Liste Des Produits ");
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Comic Sans MS", 50));
        painter.drawRect(100,100,7300,1900);
        painter.setPen(Qt::blue);
        painter.drawPixmap(QRect(7200,70,2600,2200),QPixmap("C:/Users/sarra/Desktop/inf.png"));
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
                QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/sarra/Desktop/Gestion_Stock/PDF/sarra.pdf"));
                painter.end();
            }
            if (reponse == QMessageBox::No)
            {
                 painter.end();
            }
}

void MainWindow::on_stat_clicked()
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






void MainWindow::on_qrCode_clicked()
{
    int tabeq=ui->tab_stock->currentIndex().row(); //track selected item
               QVariant idd=ui->tab_stock->model()->data(ui->tab_stock->model()->index(tabeq,0));
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
              ui->qr_code->setPixmap(QPixmap::fromImage(im));
}


void MainWindow::NumPressed(){

    // Sender returns a pointer to the button pressed
    QPushButton *button = (QPushButton *)sender();

    // Get number on button
    QString butVal = button->text();

    // Get the value in the display
    QString displayVal = ui->Display->text();

    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){

        // calcVal = butVal.toDouble();
        ui->Display->setText(butVal);

    } else {
        // Put the new number to the right of whats there
        QString newVal = displayVal + butVal;

        // Double version of number
        double dblNewVal = newVal.toDouble();

        // calcVal = newVal.toDouble();

        // Set value in display and allow up to 16
        // digits before using exponents
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));

    }
}

void MainWindow::MathButtonPressed(){

    // Cancel out previous math button clicks
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    // Store current value in Display
    QString displayVal = ui->Display->text();
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
    ui->Display->setText("");

}

void MainWindow::EqualButtonPressed(){

    // Holds new calculation
    double solution = 0.0;

    // Get value in display
    QString displayVal = ui->Display->text();
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
    ui->Display->setText(QString::number(solution));






    if(solution > 100000 )
    {


                    QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                          QObject::tr("Quantité Dépassée\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }


}

void MainWindow::ChangeNumberSign(){

    // Get the value in the display
    QString displayVal = ui->Display->text();

    // Regular expression checks if it is a number
    // plus sign
    QRegExp reg("[-+]?[0-9.]*");

    // If it is a number change the sign
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        // Put solution in display
        ui->Display->setText(QString::number(dblDisplayValSign));

    }


}









void MainWindow::on_rech_nom_clicked()
{
    ui->tab_stock->setModel(S.recherche_nom(ui->input_rech->text()));

    // ui->tab_stock->setModel(S.recherche_date(ui->date->date()));


         /* QDate datep=ui->input_rech->text().date();
                QDate datep=ui->date;
                ui->tab_stock->setModel(S.recherche_date(datep));*/
                QMessageBox::information(nullptr,QObject::tr("OK"),
                                          QObject::tr("recherche effectue.\n"
                                                      "clic cancel to exit."),QMessageBox::Cancel);

}


#include "statistique.h"
#include "ui_statistique.h"

statistique::statistique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistique)
{
    ui->setupUi(this);
}

statistique::~statistique()
{
    delete ui;
}
int statistique::Stat_partie2()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from stock where quantite BETWEEN '0' AND '99'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;

}
int statistique::Stat_partie3()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from stock where quantite BETWEEN '100' AND '500'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;

}




void statistique::paintEvent(QPaintEvent *)
{

    int b=Stat_partie2();
    //cout<<b<<endl ;
    int c=Stat_partie3();
   // cout<<c<<endl ;


        float s2= b*100 ;
        float s3=c*100;
        float nb = b+c ;
        float q2 ;
        q2 = s2/nb ;
        float q3;
        q3=s3/nb;
        float y  ;
        y = (q2*360)/100 ;
        float m;
        m= (q3*360)/100;

    QPainter painter(this);
    QRectF size=QRectF(50,50,this->width()-500,this->width()-500);

    painter.setBrush(Qt::blue);
    painter.drawPie(size,0,16*y);
    //ui->label->setText("blue:1-100") ;
    painter.setBrush(Qt::black);
    painter.drawPie(size,16*y,16*m);
    //ui->label_2->setText("green:101-500") ;
    painter.setBrush(Qt::red);


}

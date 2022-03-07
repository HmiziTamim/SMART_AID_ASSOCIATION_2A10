#include "connection.h"

//Test Tutoriel Git

Connection::Connection()
{

}

bool Connection::createconnect()
{
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC"); //intialisation

bool test=false;
db.setDatabaseName("Source_Projet2A");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("sarra1234");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;



}

void Connection::closeconnect(){db.close();}

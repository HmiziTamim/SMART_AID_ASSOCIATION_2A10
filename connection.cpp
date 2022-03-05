#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Projet2A");
db.setUserName("tamim");//inserer nom de l'utilisateur
db.setPassword("1007");//inserer mot de passe de cet utilisateur
if (db.open())
test=true;
    return  test;
}

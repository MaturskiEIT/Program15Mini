#include "konekcija.h"

Konekcija::Konekcija()
{

}

bool Konekcija::dbOpen()
{
    db.open();

    QSqlQuery upit;
    upit.exec("PRAGMA foreign_key = ON;");

    return true;
}

void Konekcija::dbClose()
{
    db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

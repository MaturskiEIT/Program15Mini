#include "glavniprozor.h"
#include "ui_glavniprozor.h"
#include "konekcija.h"
#include "knjige.h"
#include "poknjigama.h"

GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor)
{
    ui->setupUi(this);
}

GlavniProzor::~GlavniProzor()
{
    delete ui;
}

void GlavniProzor::on_actionIzlaz_triggered()
{
    this->close();
}

void GlavniProzor::on_actionKnjige_triggered()
{
    Knjige *k = new Knjige(this);
    k->setModal(true);
    k->show();
}

void GlavniProzor::on_actionPo_knjigama_triggered()
{
    PoKnjigama *pk = new PoKnjigama(this);
    pk->setModal(true);
    pk->show();
}

#include "poknjigama.h"
#include "ui_poknjigama.h"
#include "konekcija.h"
#include <QMessageBox>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

using namespace QtCharts;

PoKnjigama::PoKnjigama(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PoKnjigama)
{
    ui->setupUi(this);

    Konekcija baza;
    baza.dbOpen();

    QSqlQuery upit;

    upit.prepare("SELECT KnjigaID, Naziv FROM Knjiga ORDER BY KnjigaID ASC;");

    upit.exec();

    QStringList listaKnjiga;
    while(upit.next())
    {
        listaKnjiga.append(upit.value(0).toString() + " - " + upit.value(1).toString());
    }
    QStringListModel *model;
    model = new QStringListModel();
    model->setStringList(listaKnjiga);
    ui->comboBoxKnjiga->setModel(model);

    baza.dbClose();
}

PoKnjigama::~PoKnjigama()
{
    delete ui;
}

void PoKnjigama::on_pushButtonIzadji_clicked()
{
    this->close();
}

void PoKnjigama::on_pushButtonPrikazi_clicked()
{
    QString godina = ui->lineEditGodina->text();
    QString knjigaID = ui->comboBoxKnjiga->currentText();
    knjigaID.truncate(knjigaID.indexOf(" - "));

    Konekcija baza;
    baza.dbOpen();

    QSqlQuery upit;

    upit.prepare("SELECT Na_Citanju.DatumUzimanja FROM Knjiga INNER JOIN Na_Citanju ON Knjiga.KnjigaID = Na_Citanju.KnjigaID WHERE (Knjiga.KnjigaID = :knjigaID) AND (Na_Citanju.DatumUzimanja LIKE '%" + godina + "');");
    upit.bindValue(":knjigaID", knjigaID);

    upit.exec();

    int brojIznajmljenihKnjigaPoMesecima[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    while(upit.next())
    {
        QDateEdit datum;
        datum.setDate(QDate::fromString(upit.value(0).toString()));
        int mesecBroj = datum.date().month();
        brojIznajmljenihKnjigaPoMesecima[mesecBroj]++;
    }

    QLineSeries *serija = new QLineSeries();
    serija->setName("Broj citaoca");
    for(int i = 0; i < 14; i++)
        serija->append(i, brojIznajmljenihKnjigaPoMesecima[i]);

    QChart *grafikon = new QChart();
    grafikon->addSeries(serija);

    QStringList nazivMeseci;
    nazivMeseci << " " << "Januar" << "Februar" << "Mart" << "April" << "Maj" << "Jun" << "Jul" << "Avgust" << "Septembar" << "Oktobar" << "Novembar" << "Decembar" << " ";

    grafikon->createDefaultAxes();

    QCategoryAxis *osaX = new QCategoryAxis();
    osaX->append(" ", 1);
    osaX->append("Februar", 3);
    osaX->append("April", 5);
    osaX->append("Jun", 7);
    osaX->append("Avgust", 9);
    osaX->append("Oktobar", 11);
    osaX->append("Decembar", 13);
    osaX->append(" ", 14);
    grafikon->setAxisX(osaX, serija);

    grafikon->axisY()->setMin(0);

    grafikon->legend()->setVisible(true);
    grafikon->legend()->setAlignment(Qt::AlignTop);

    QChartView *chartView = new QChartView(grafikon);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView, 0, 0);

    baza.dbClose();
}

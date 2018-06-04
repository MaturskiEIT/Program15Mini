#ifndef KNJIGE_H
#define KNJIGE_H

#include <QDialog>

namespace Ui {
class Knjige;
}

class Knjige : public QDialog
{
    Q_OBJECT

public:
    explicit Knjige(QWidget *parent = 0);
    ~Knjige();

private slots:
    void on_pushButtonIzadji_clicked();

    void on_lineEditSifra_editingFinished();

    void on_pushButtonObrisi_clicked();

    void on_pushButtonIzmeni_clicked();

    void on_pushButtonUpisi_clicked();

private:
    Ui::Knjige *ui;
};

#endif // KNJIGE_H

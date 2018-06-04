#ifndef POKNJIGAMA_H
#define POKNJIGAMA_H

#include <QDialog>

namespace Ui {
class PoKnjigama;
}

class PoKnjigama : public QDialog
{
    Q_OBJECT

public:
    explicit PoKnjigama(QWidget *parent = 0);
    ~PoKnjigama();

private slots:
    void on_pushButtonIzadji_clicked();

    void on_pushButtonPrikazi_clicked();

private:
    Ui::PoKnjigama *ui;
};

#endif // POKNJIGAMA_H

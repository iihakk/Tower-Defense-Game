#ifndef SECONDHELPER_H
#define SECONDHELPER_H

#include <QDialog>

namespace Ui {
class secondhelper;
}

class secondhelper : public QDialog
{
    Q_OBJECT

public:
    explicit secondhelper(QWidget *parent = nullptr);
    ~secondhelper();

private slots:
    void on_next_clicked();

    void on_Back_clicked();

private:
    Ui::secondhelper *ui;
};

#endif // SECONDHELPER_H

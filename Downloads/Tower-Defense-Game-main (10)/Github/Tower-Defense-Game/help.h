#ifndef HELP_H
#define HELP_H

#include <QDialog>

namespace Ui {
class help;
}

class help : public QDialog
{
    Q_OBJECT

public:
    explicit help(QWidget *parent = nullptr);
    ~help();

private slots:
    void on_backbutton_clicked();

    void on_Nextbutton_clicked();

private:
    Ui::help *ui;
};

#endif // HELP_H

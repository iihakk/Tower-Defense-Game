#ifndef THIRDHELP_H
#define THIRDHELP_H

#include <QDialog>
#include "map.h"
#include "gamecontroller.h"

namespace Ui {
class thirdhelp;
}

class thirdhelp : public QDialog
{
    Q_OBJECT

public:
    explicit thirdhelp(QWidget *parent = nullptr);
    ~thirdhelp();

private slots:
    void on_proceed_clicked();

    void on_backbutton_clicked();

private:
    Ui::thirdhelp *ui;

    Map* map;

    GameController gamecontroller;

    QGraphicsView* view ;
};

#endif // THIRDHELP_H

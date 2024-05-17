#ifndef HELP_H
#define HELP_H

#include <QDialog>
#include <QGraphicsView>
#include "map.h"
#include "gamecontroller.h"

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
    Map* map;
    GameController* gameController = nullptr;
    QGraphicsView* view ;
    QSoundEffect* gameMusic;

};

#endif // HELP_H

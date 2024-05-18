#ifndef STARTMENU_H
#define STARTMENU_H

#include <QDialog>
#include "map.h"
#include "gamecontroller.h"
#include "QSoundEffect"
#include "QMediaPlayer"


namespace Ui {
class StartMenu;
}

class StartMenu : public QDialog
{
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

    static void click();

private slots:
    void on_startbutton_clicked();

    void on_helpbutton_clicked();

private:
    Ui::StartMenu *ui;

    QSoundEffect* gameMusic;

    Map* map;

    GameController* gameController = nullptr;

    QGraphicsView* view ;

};

#endif

#include "startmenu.h"
#include "ui_startmenu.h"
#include "help.h"
#include <gamecontroller.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QApplication>
#include <gamecontroller.h>


StartMenu::StartMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartMenu)
    , map(new Map(1)) // Instantiate Map object
    , view(NULL)
{
    ui->setupUi(this);
    ui->towerDefenseTitleLabel->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->towerDefenseTitleLabel->hide();
    gameMusic = new QSoundEffect(this);
    gameMusic->setLoopCount(20);
    gameMusic->setSource(QUrl("qrc:/Music/GameMusic.wav"));
}

StartMenu::~StartMenu()
{
    delete ui;
    delete map; // Delete the map object
    delete view; // Delete the view object

}

void StartMenu::on_startbutton_clicked()
{
    hide();

    gameMusic->play();
    view = new QGraphicsView();
    view->setScene(map);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    view->setFixedSize(1400, 700);
    view->viewport()->setAttribute(Qt::WidgetAttribute::WA_AcceptTouchEvents, false);

    gameController = new GameController(map,1, view);


}


void StartMenu::on_helpbutton_clicked()
{
    hide();
    help *helpwindow = new help(this);
    helpwindow -> show();    
}




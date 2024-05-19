#include "help.h"
#include "ui_help.h"
#include "startmenu.h"

help::help(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::help)
    , map(new Map(1)) // Instantiate Map object
    , view(NULL)
{
    ui->setupUi(this);
    ui->informationLineEdit->setReadOnly(true);
    ui->gameObjectivesLabel->setAttribute(Qt::WA_TintedBackground, true);
    ui->gameObjectivesLabel->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->informationLineEdit->setAttribute(Qt::WA_TintedBackground, true);
    ui->informationLineEdit->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->informationLineEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->informationLineEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    gameMusic = new QSoundEffect(this);
    gameMusic->setSource(QUrl("qrc:/Music/GameMusic.wav"));
}

help::~help()
{
    delete ui;
}

//return to the start menu
void help::on_backbutton_clicked()
{
    hide();
    StartMenu *startwindow = new StartMenu(this);
    startwindow -> show();
}

//if the next button is clicked, show the next text
//if the let's go button is clicked, start the game
void help::on_Nextbutton_clicked()
{
    if(ui->Nextbutton->text() == "Next"){
        ui->informationLineEdit->setText("You have limited health, and a limited budget! Select a tile, buy an item through the shop, and "
                                         "it will be automatically placed on the selected tile. Upgrade towers by selecting the tower you wish to upgrade and clicking upgrade to increase their attributes. Enjoy~~");
        ui->Nextbutton->setText("Let's Go");
    }
    else if(ui->Nextbutton->text() == "Let's Go"){
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
}


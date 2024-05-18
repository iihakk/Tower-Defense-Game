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

void help::on_backbutton_clicked()
{
    hide();
    StartMenu *startwindow = new StartMenu(this);
    startwindow -> show();
}


void help::on_Nextbutton_clicked()
{
    if(ui->Nextbutton->text() == "Next"){
        ui->informationLineEdit->setText("You have a limited health, and a limited budget! Select a tile, buy an item through the shop, and "
                                         "it will be placed on the selected tile. Upgrade towers to increase their attributes. Enjoy~~");
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


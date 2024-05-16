#include "help.h"
#include "ui_help.h"
#include "startmenu.h"
#include "secondhelper.h"

help::help(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::help)
{
    ui->setupUi(this);
    ui->informationLineEdit->setReadOnly(true);
    ui->gameObjectivesLabel->setAttribute(Qt::WA_TintedBackground, true);
    ui->gameObjectivesLabel->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->informationLineEdit->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->informationLineEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->informationLineEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
        ui->informationLineEdit->setText("You have a limited health, and a limited budget! Buy towers from shop, and "
                                     "place them on the tiles you choose. Enjoy~~");
        ui->Nextbutton->setText("Let's Go");
    }
    else if(ui->Nextbutton->text() == "Let's Go"){

    }
}


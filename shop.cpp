#include "shop.h"
#include "ui_shop.h"
#include "QPixmap"
#include <QFont>


Shop::Shop(QWidget *parent, Map* originalmap)
    : QDialog(parent)
    , ui(new Ui::Shop),
    map(originalmap)
{

    ui->setupUi(this);

    //set pictures for every tower
    QPixmap cannonT(":/TowerImages/Cannon1.png");
    QPixmap infernoT(":/TowerImages/inferno1.png");
    QPixmap teslaT(":/TowerImages/Tesla1.png");
    QPixmap XbowT(":/TowerImages/Xbow1.png");

    //get width and height of picture
    int w = ui->cannon->width();
    int h = ui->cannon->height();

    // assign the picture to their slots

    ui->cannon->setPixmap(cannonT.scaled(w,h,Qt::KeepAspectRatio));
    ui->inferno->setPixmap(infernoT.scaled(w,h,Qt::KeepAspectRatio));
    ui->tesla->setPixmap(teslaT.scaled(w,h,Qt::KeepAspectRatio));
    ui->Xbow->setPixmap(XbowT.scaled(w,h,Qt::KeepAspectRatio));

    ui->insufficientbalance->setVisible(false);

    QFont font("Arial", 12);

    ui->coinbalance->setFont(font);
    ui->coinbalance->setText("Coin Balance: " + QString::number(map->getcoinbalance()));

}

Shop::~Shop()
{
    delete ui;
    delete map;

}

void Shop::on_back_clicked()
{
    hide();
}


void Shop::on_cannonbuy_clicked()
{
    if (map->Coins < 500){
        ui->insufficientbalance->setVisible(true);
    }
    else {
        hide();
        emit deploycannon();
    }

}


void Shop::on_infernobuy_clicked()
{
    if (map->Coins < 750){
        ui->insufficientbalance->setVisible(true);
    }
    else {
        hide();
        emit deployinferno();
    }
}


void Shop::on_xbowbuy_clicked()
{
    if (map->Coins < 1000){
        ui->insufficientbalance->setVisible(true);
    }
    else {
        hide();
        emit deployxbow();
    }
}


void Shop::on_teslabuy_clicked()
{
    if (map->Coins < 1500){
        ui->insufficientbalance->setVisible(true);
    }
    else {
        hide();
        emit deploytesla();
    }
}

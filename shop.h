#ifndef SHOP_H
#define SHOP_H

#include <QDialog>
#include "map.h"

namespace Ui {
class Shop;
}

class Shop : public QDialog
{
    Q_OBJECT

public:
    explicit Shop(QWidget *parent = nullptr, Map* map = NULL);
    ~Shop();

signals:
    void deployxbow();
    void deploycannon();
    void deploytesla();
    void deployinferno();


private slots:
    void on_back_clicked();

    void on_cannonbuy_clicked();

    void on_infernobuy_clicked();

    void on_xbowbuy_clicked();

    void on_teslabuy_clicked();

private:
    Ui::Shop *ui;

    Map *map;
};

#endif // SHOP_H

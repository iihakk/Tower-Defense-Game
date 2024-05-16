#include "thirdhelp.h"
#include "ui_thirdhelp.h"
#include "secondhelper.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QApplication>
#include "map.h"
#include <gamecontroller.h>


thirdhelp::thirdhelp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::thirdhelp)
    , map(new Map(5)) // Instantiate Map object
    , gamecontroller(map) // Instantiate GameController object with Map
    , view(NULL)
{
    ui->setupUi(this);
    ui -> objective -> setReadOnly(true);
    ui -> textEdit -> setReadOnly(true);
}

thirdhelp::~thirdhelp()
{
    delete ui;
    delete map; // Delete the map object
    delete view; // Delete the view object
}


void thirdhelp::on_proceed_clicked()
{
    hide();

    view = new QGraphicsView();
    view->setScene(map);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    view->setFixedSize(1400, 700);
    //view->setAttribute(Qt::WA_AcceptTouchEvents, false);
    view->viewport()->setAttribute(Qt::WidgetAttribute::WA_AcceptTouchEvents, false);


}
void thirdhelp::on_backbutton_clicked()
{
    hide();
    secondhelper *helpwindow = new secondhelper(this);
    helpwindow-> show();
}


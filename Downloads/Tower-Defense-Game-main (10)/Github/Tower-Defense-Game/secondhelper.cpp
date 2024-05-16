#include "secondhelper.h"
#include "ui_secondhelper.h"
#include "thirdhelp.h"
#include "help.h"

secondhelper::secondhelper(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::secondhelper)
{
    ui->setupUi(this);
    ui -> objective -> setReadOnly(true);
    ui -> textEdit -> setReadOnly(true);
}

secondhelper::~secondhelper()
{
    delete ui;
}

void secondhelper::on_next_clicked()
{
    hide();
    thirdhelp *window = new thirdhelp(this);
    window-> show();
}


void secondhelper::on_Back_clicked()
{
    hide();
    help *helper = new help(this);
    helper-> show();
}


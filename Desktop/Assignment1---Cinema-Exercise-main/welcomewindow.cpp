#include "welcomewindow.h"
#include "ui_welcomewindow.h"
#include "qpixmap.h"
#include "loginwindow.h"

WelcomeWindow::WelcomeWindow(QWidget *parent, QString username, int age)
    : QDialog(parent)
    , ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);

    QString welcomeMessage= QString ("Hi %1! Your age is %2").arg(username).arg(age);
    ui->labelMessage->setText(welcomeMessage);
    QPixmap pic (":/Image/Cinema.jpg");
    int w = ui->labelPicture->width();
    int h = ui->labelPicture->height();
    ui->labelPicture->setPixmap(pic.scaled(w, h, Qt::KeepAspectRatio));

}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

void WelcomeWindow::on_pushButtonLogout_clicked()
{
    LoginWindow *loginWindow = new LoginWindow(this);
    loginWindow->show();
    hide();
}


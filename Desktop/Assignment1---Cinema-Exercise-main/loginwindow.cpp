#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "Users.h"
#include "welcomewindow.h"
#include "registerwindow.h"

bool validation (QString EnteredU, QString EnteredP)
{
    for (int i = 0; i < userCount; i++){
        if (usernames[i]== EnteredU and passwords [i]== EnteredP){
             return 1;
            }
                }return 0;}

int ageIndex (QString username){
    for (int i = 0 ; i<userCount; i++){
    if (username == usernames[i])
            return ages[i];}
     return -1;
}

bool validation (QString user, QString pass);
LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->ErrorLabel->setVisible(0);
}

LoginWindow::~LoginWindow()
{
    delete ui;

}

void LoginWindow::on_pushButtonLogin_clicked()
{
    QString EnteredUsername = ui->LineEditUsername->text();
    QString EnteredPassword = ui->LineEditPassword->text();
    if (validation(EnteredUsername, EnteredPassword)) {
        WelcomeWindow *welcomeWindow = new WelcomeWindow(this, ui->LineEditUsername->text(), ageIndex(ui->LineEditUsername->text()));
        welcomeWindow->show();
        hide();
    }
    else ui->ErrorLabel->setVisible(1);
    }


void LoginWindow::on_pushButtonRegister_clicked()
{
    RegisterWindow *registerwindow = new RegisterWindow(this);
    registerwindow->show();
    hide();
}


#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "Users.h"
#include "welcomewindow.h"

RegisterWindow::RegisterWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    ui->UsernameError->hide();
    ui->MatchingError->hide();
    ui->AgeError->hide();
    ui->RegisterError->hide();
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_RegisterButton_clicked()
{
    ui->UsernameError->hide();
    ui->MatchingError->hide();
    ui->AgeError->hide();
    ui->RegisterError->hide();
    bool error = false;
    QString username = ui->Username->text();
    QString pass1 = ui->Password->text();
    QString pass2 = ui->Password2->text();
    int month=ui->MonthBox->currentIndex();
    int day = ui->DayBox->currentIndex();
    int year=ui->YearBox->currentText().toInt();
    bool male = ui->MateButton->isChecked();
    bool female = ui->FemaleButton->isChecked();
    bool user = ui->UserButton->isChecked();
    bool admin =ui->AdminButton->isChecked();
    bool action =ui->ActionBox->isChecked();
    bool comedy =ui->ComedyBox->isChecked();
    bool romance =ui->RomanceBox->isChecked();
    bool drama =ui->DramaBox->isChecked();
    bool horror =ui->HorrorBox->isChecked();
    bool other =ui->OtherBox->isChecked();
    for (int i=0; i<userCount; i++)
    {
        if (username==usernames[i])
        {
            ui->UsernameError->show();
            error=true;
            break;
        }
    }
    if (pass1!=pass2)
    {
        ui->MatchingError->show();
        error = true;
    }
    if ((2024-year)<12)
    {
        ui->AgeError->show();
        error=true;
    }
    if ((username=="")||(pass1=="")||(pass2=="")||((!male)&&(!female))||((!user)&&(!admin))||((!action)&&(!comedy)&&(!romance)&&(!drama)&&(!horror)&&(!other)))
    {
        ui->RegisterError->show();
        error = true;
    }
    if (!error)
    {

        usernames[userCount]=username;
        passwords[userCount]=pass1;
        ages[userCount]=2024-year;
        userCount++;
        WelcomeWindow *welcomeWindow = new WelcomeWindow(this, username, ages[userCount]);
        welcomeWindow->show();
        hide();
    }
}


#include "tower.h"
#include <QTimer>
#include <QMessageBox>
#include <QString>

// base tower instantiation with its properties and sets the QGraphicsItem as parent
Tower::Tower(int dmg, int hlth, int cst, int rng, int fireR, Map* map)
    : Damage(dmg), Health(hlth), Cost(cst), Range(rng), FiringRate(fireR),
    UpgradeCost(cst), UpgradeLevel(0), map(map) {

    map->addItem(this);

    towerShootingTimer = new QTimer();
    connect(towerShootingTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    towerShootingTimer->start(4000/FiringRate);
}

Tower::~Tower(){
    towerShootingTimer->stop();
    this->scene()->removeItem(this);
}

// function to be used for upgrading
void Tower::increaseAttributes(int dmgIncrease, int rangeIncrease, int rateIncrease, int costIncrease) {
    Damage += dmgIncrease;
    Range += rangeIncrease;
    FiringRate += rateIncrease;
    UpgradeCost += costIncrease;
}

int Tower::getlevel()
{
    return UpgradeLevel;
}

bool Tower::upgrademsg()
{
    QString message = "Are you sure you want to upgrade the tower? this will cost you " + QString::number(UpgradeCost) + " coins";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(NULL, "Upgrade Tower",message,
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes){
        return true;
    }
    else {
        return false;
    }
}

void Tower::maximumtowerlevel()
{
    QMessageBox *maxTowerLevelBox = new QMessageBox();
    maxTowerLevelBox->setWindowTitle("Maximum Tower Level");
    maxTowerLevelBox->setText("You've reached the maximum level for this tower.");
    maxTowerLevelBox->show();
}

void Tower::insufficientbalance()
{
    QMessageBox *insufficientCoinsBox = new QMessageBox();
    insufficientCoinsBox->setWindowTitle("Insufficient Balance");
    insufficientCoinsBox->setText("You don't have enough coins to upgrade this tower");
    insufficientCoinsBox->show();
}

void Tower::handleDeleteBulletSignal(Bullet* bullet){
    bullets.removeAll(bullet);
    delete bullet;
}

int Tower::getRange(){
    return Range;
}

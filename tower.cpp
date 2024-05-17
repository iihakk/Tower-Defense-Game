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
    for(Bullet* bullet: bullets){
        this->scene()->removeItem(bullet);
    }
    this->scene()->removeItem(this);
}

// function to be used for upgrading
void Tower::increaseAttributes(int dmgIncrease, int rangeIncrease, int rateIncrease, int costIncrease) {
    Damage += dmgIncrease;
    Range += rangeIncrease;
    FiringRate += rateIncrease;
    UpgradeCost += costIncrease;
}

void Tower::stopShootingTimer(){
    towerShootingTimer->stop();
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
    maxTowerLevelBox->setFont(QFont("Franklin Gothic Heavy"));
    maxTowerLevelBox->show();
}

void Tower::insufficientbalance()
{
    QMessageBox *insufficientCoinsBox = new QMessageBox();
    insufficientCoinsBox->setWindowTitle("Insufficient Balance");
    insufficientCoinsBox->setText("You don't have enough coins to upgrade this tower");
    insufficientCoinsBox->show();
}


//Change the closest enemy to the specified enemy
void Tower::setClosestEnemy(Enemy* enemy){
    closestEnemy = enemy;
}

//Returns the closest enemy
Enemy* Tower::getClosestEnemy() const{
    return closestEnemy;
}

//Change the list of enemies
void Tower::setEnemies(QList<Enemy*>& enemies){
    this->enemies = enemies;
}

//Calculate the distance between two points
double Tower::calculateDistance(const QPointF& from, const QPointF& to) {
    return sqrt(pow(from.x() - to.x(), 2) + pow(from.y() - to.y(), 2));
}

//Find the closest enemy within range
Enemy* Tower::findClosestEnemyWithinRange(){

    //Set the closest enemy to be at infinite distance
    double closestEnemyDistance = INT_MAX;
    int indexClosestEnemy = -1;
    double currentDistance = INT_MAX;
    for(int i = 0; i < enemies.size();i++){
        if(enemies[i]->scene() == map){
            QPointF enemyPos = enemies[i]->pos();
            currentDistance = calculateDistance(enemyPos, this->pos());
            if(currentDistance <= Range && currentDistance < closestEnemyDistance){ //If the enemy is closer than the closest enemy and within range update the closest
                closestEnemyDistance = currentDistance;
                indexClosestEnemy = i;
            }
        }
    }

    if(indexClosestEnemy == -1){
        return nullptr;
    }

    if(enemies[indexClosestEnemy]){
        return enemies[indexClosestEnemy];
    }

    return nullptr;
}

void Tower::handleDeleteBulletSignal(Bullet* bullet){
    bullets.removeAll(bullet);
    delete bullet;
}

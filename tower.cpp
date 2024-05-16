#include "tower.h"
#include <QTimer>
#include <iostream>

// base tower instantiation with its properties and sets the QGraphicsItem as parent
Tower::Tower(int dmg, int hlth, int cst, int rng, int fireR, Map* map)
    : Damage(dmg), Health(hlth), Cost(cst), Range(rng), FiringRate(fireR),
    UpgradeCost(cst), UpgradeLevel(0), map(map) {

    map->addItem(this);

    towerShootingTimer = new QTimer();
    connect(towerShootingTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    towerShootingTimer->start(1000);
}

// Tower::~Tower(){
//     for(CannonBullet* bullet: bullets){
//         delete bullet;
//     }
//     this->scene()->removeItem(this);
// }

Tower::~Tower(){
    for(Bullet* bullet: bullets){
        this->scene()->removeItem(this);
    }
}

// function to be used for upgrading
void Tower::increaseAttributes(int dmgIncrease, int rangeIncrease, int rateIncrease, int costIncrease) {
    Damage += dmgIncrease;
    Range += rangeIncrease;
    FiringRate += rateIncrease;
    UpgradeCost += costIncrease;
}

// void Tower::shoot(){
//     closestEnemy = findClosestEnemyWithinRange(); //Find the closest enemy
//     if(closestEnemy){
//         QPointF position = this->pos();
//         position.setX(this->x()+50);
//         position.setY(this->y()+50);
//         CannonBullet* bullet = new CannonBullet(map, position, Damage, closestEnemy); //create a new bullet with the specified map, position, damage, and enemy
//         bullets.append(bullet); //append the bullet to the list of bullets shot by the tower
//     }
// }

// void Tower::shoot(){
//     closestEnemy = findClosestEnemyWithinRange(); //Find the closest enemy
//     if(closestEnemy){
//         QPointF position = this->pos();
//         position.setX(this->x()+50);
//         position.setY(this->y()+50);
//         InfernoBullet* bullet = new InfernoBullet(map, position, Damage, closestEnemy); //create a new bullet with the specified map, position, damage, and enemy
//         bullets.append(bullet); //append the bullet to the list of bullets shot by the tower
//     }
// }

void Tower::stopShootingTimer(){
    towerShootingTimer->stop();
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

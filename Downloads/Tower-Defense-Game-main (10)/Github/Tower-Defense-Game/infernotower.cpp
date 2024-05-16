#include "infernotower.h"

const std::vector<QString> InfernoTower::levelImages = {
    ":/TowerImages/inferno1.png",
    ":/TowerImages/inferno2.png",
    ":/TowerImages/inferno3.png"
};

InfernoTower::InfernoTower(Map* map) : Tower(15, 200, 120, 250, 1, map) {
    setLevelImage();
}

InfernoTower::InfernoTower(Map* map, int posX, int posY) : InfernoTower(map) {
    setLevelImage();
    this->setX(posX);
    this->setY(posY);
}

bool InfernoTower::upgrade(int& playerCurrency) {
    if (UpgradeLevel < MaxUpgradeLevel && playerCurrency >= UpgradeCost) {
        increaseAttributes(3, 10, 2, 75);
        playerCurrency -= UpgradeCost;
        UpgradeCost += 75;
        UpgradeLevel++;
        return true;
    }
    return false;
}

void InfernoTower::setLevelImage() {
    setPixmap(QPixmap(levelImages[UpgradeLevel]).scaled(100,100));
}

void InfernoTower::shoot(){
    closestEnemy = findClosestEnemyWithinRange(); //Find the closest enemy
    if(closestEnemy){
        QPointF position = this->pos();
        position.setX(this->x()+50);
        position.setY(this->y()+50);
        InfernoBullet* bullet = new InfernoBullet(map, position, Damage, closestEnemy); //create a new bullet with the specified map, position, damage, and enemy
        bullets.append(bullet); //append the bullet to the list of bullets shot by the tower
    }
}

#include "cannontower.h"

const std::vector<QString> CannonTower::levelImages = {
    ":/TowerImages/Cannon1.png",
    ":/TowerImages/Cannon2.png",
    ":/TowerImages/Cannon3.png"
};

CannonTower::CannonTower(Map* map) : Tower(10, 150, 100, 200, 1, map) {
    setLevelImage();
}

CannonTower::CannonTower(Map* map, int posX, int posY) : CannonTower(map){
    setLevelImage();
    this->setX(posX);
    this->setY(posY);
}

bool CannonTower::upgrade(int& playerCurrency) {
    if (UpgradeLevel < MaxUpgradeLevel && playerCurrency >= UpgradeCost) {
        increaseAttributes(2, 5, 1, 50);
        playerCurrency -= UpgradeCost;
        UpgradeCost += 50;
        UpgradeLevel++;
        return true;
    }
    return false;
}

void CannonTower::setLevelImage() {
    setPixmap(QPixmap(levelImages[UpgradeLevel]).scaled(100,100));
}

void CannonTower::shoot(){
    closestEnemy = findClosestEnemyWithinRange(); //Find the closest enemy
    if(closestEnemy){
        QPointF position = this->pos();
        position.setX(this->x()+50);
        position.setY(this->y()+50);
        CannonBullet* bullet = new CannonBullet(map, position, Damage, closestEnemy); //create a new bullet with the specified map, position, damage, and enemy
        bullets.append(bullet); //append the bullet to the list of bullets shot by the tower
    }
}

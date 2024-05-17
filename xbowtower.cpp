#include "xbowtower.h"

const std::vector<QString> XbowTower::levelImages = {
    ":/TowerImages/Xbow1.png",
    ":/TowerImages/Xbow2.png",
    ":/TowerImages/Xbow3.png"
};

XbowTower::XbowTower(Map* map) : Tower(1, 150, 200, 300, 20, map) {
    setLevelImage();
}

XbowTower::XbowTower(Map* map, int posX, int posY) : XbowTower(map) {
    setLevelImage();
    this->setX(posX);
    this->setY(posY);
}

bool XbowTower::upgrade(int& playerCurrency) {
    ConfirmUpgrade = upgrademsg();

    if (ConfirmUpgrade == true){
        if (UpgradeLevel < MaxUpgradeLevel) {
            if (playerCurrency >= UpgradeCost){
                playerCurrency -= UpgradeCost;
                increaseAttributes(5, 20, 3, 100);
                UpgradeLevel++;
                setLevelImage();
                return true;
            }
            else{
                insufficientbalance();
            }
        }
    }
    return false;
}




void XbowTower::setLevelImage() {
    setPixmap(QPixmap(levelImages[UpgradeLevel]).scaled(100, 100));
}

void XbowTower::shoot() {
    closestEnemy = findClosestEnemyWithinRange(); // Find the closest enemy
    if (closestEnemy) {
        QPointF position = this->pos();
        position.setX(this->x() + 50);
        position.setY(this->y() + 50);
        XbowBullet* bullet = new XbowBullet(map, position, Damage, closestEnemy); // Create a new bullet with the specified map, position, damage, and enemy
        bullets.append(bullet); // Append the bullet to the list of bullets shot by the tower
        connect(bullet, SIGNAL(deleteBulletSignal(Bullet*)), this, SLOT(handleDeleteBulletSignal(Bullet*)));
    }
}

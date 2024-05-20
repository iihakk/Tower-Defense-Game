#include "xbowtower.h"

const std::vector<QString> XbowTower::levelImages = {
    ":/TowerImages/Xbow1.png",
    ":/TowerImages/Xbow2.png",
    ":/TowerImages/Xbow3.png"
};

XbowTower::XbowTower(Map* map) : Tower(4, 150, 350, 300, 20, map) {
    setLevelImage();
}

XbowTower::XbowTower(Map* map, int posX, int posY) : XbowTower(map) {
    this->setX(posX);
    this->setY(posY);
}

bool XbowTower::upgrade(int& playerCurrency) {
    ConfirmUpgrade = upgrademsg();

    if (ConfirmUpgrade == true){
        if (UpgradeLevel < MaxUpgradeLevel) {
            if (playerCurrency >= UpgradeCost){
                playerCurrency -= UpgradeCost;
                increaseAttributes(1, 0, 0, 150);
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
    emit Tower::shoot(this);
}

void XbowTower::shoot(Enemy* enemy){
    if(enemy){
        QPointF position = this->pos();
        position.setX(this->x()+50);
        position.setY(this->y()+50);
        Bullet* bullet = new XbowBullet(map, position, Damage, enemy); //create a new bullet with the specified map, position, damage, and enemy
        bullets.append(bullet); //append the bullet to the list of bullets shot by the tower
        connect(bullet, SIGNAL(deleteBulletSignal(Bullet*)), this, SLOT(handleDeleteBulletSignal(Bullet*)));
    }
}

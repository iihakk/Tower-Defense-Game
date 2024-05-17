#include "cannontower.h"

const std::vector<QString> CannonTower::levelImages = {
    ":/TowerImages/Cannon1.png",
    ":/TowerImages/Cannon2.png",
    ":/TowerImages/Cannon3.png"
};

CannonTower::CannonTower(Map* map) : Tower(40, 100, 100, 200, 1, map) {
    setLevelImage();
}

CannonTower::CannonTower(Map* map, int posX, int posY) : CannonTower(map){
    setLevelImage();
    this->setX(posX);
    this->setY(posY);
}

bool CannonTower::upgrade(int& playerCurrency) {
    ConfirmUpgrade = upgrademsg();

    if (ConfirmUpgrade == true){
            if (playerCurrency >= UpgradeCost){
                playerCurrency -= UpgradeCost;
                increaseAttributes(10, 10, 0, 50);
                UpgradeLevel++;
                setLevelImage();
                return true;
            }
            else{
                insufficientbalance();
            }
    }
    return false;
}

void CannonTower::setLevelImage() {
    setPixmap(QPixmap(levelImages[UpgradeLevel]).scaled(100,100));
}

void CannonTower::shoot(){
    emit Tower::shoot(this);
}

void CannonTower::shoot(Enemy* enemy){
    if(enemy){
        QPointF position = this->pos();
        position.setX(this->x()+50);
        position.setY(this->y()+50);
        Bullet* bullet = new CannonBullet(map, position, Damage, enemy); //create a new bullet with the specified map, position, damage, and enemy
        bullets.append(bullet); //append the bullet to the list of bullets shot by the tower
        connect(bullet, SIGNAL(deleteBulletSignal(Bullet*)), this, SLOT(handleDeleteBulletSignal(Bullet*)));
    }
}

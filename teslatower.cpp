#include "teslatower.h"

const std::vector<QString> TeslaTower::levelImages = {
    ":/TowerImages/Tesla1.png",
    ":/TowerImages/Tesla2.png",
    ":/TowerImages/Tesla3.png"
};

TeslaTower::TeslaTower(Map* map) : Tower(5, 180, 250, 400, 10, map) {
    setLevelImage();
}

TeslaTower::TeslaTower(Map* map, int posX, int posY) : TeslaTower(map) {
    setLevelImage();
    this->setX(posX);
    this->setY(posY);
}

bool TeslaTower::upgrade(int& playerCurrency) {

    ConfirmUpgrade = upgrademsg();

    if (ConfirmUpgrade == true){
            if (playerCurrency >= UpgradeCost){
                playerCurrency -= UpgradeCost;
                increaseAttributes(5, 0, 0, 150);
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


void TeslaTower::setLevelImage() {
    setPixmap(QPixmap(levelImages[UpgradeLevel]).scaled(100, 100));
}

void TeslaTower::shoot() {
    emit Tower::shoot(this);
}

void TeslaTower::shoot(Enemy* enemy){
    if(enemy){
        QPointF position = this->pos();
        position.setX(this->x()+50);
        position.setY(this->y()+50);
        Bullet* bullet = new TeslaBullet(map, position, Damage, enemy); //create a new bullet with the specified map, position, damage, and enemy
        bullets.append(bullet); //append the bullet to the list of bullets shot by the tower
        connect(bullet, SIGNAL(deleteBulletSignal(Bullet*)), this, SLOT(handleDeleteBulletSignal(Bullet*)));
    }
}

#include "infernotower.h"

const std::vector<QString> InfernoTower::levelImages = {
    ":/TowerImages/inferno1.png",
    ":/TowerImages/Inferno2.png",
    ":/TowerImages/Inferno3.png"
};

InfernoTower::InfernoTower(Map* map) : Tower(20, 200, 120, 250, 4, map) {
    setLevelImage();
}

InfernoTower::InfernoTower(Map* map, int posX, int posY) : InfernoTower(map) {
    this->setX(posX);
    this->setY(posY);
}

//upgrade the inferno
bool InfernoTower::upgrade(int& playerCurrency) {
    ConfirmUpgrade = upgrademsg();

    if (ConfirmUpgrade == true){
            if (playerCurrency >= UpgradeCost){
                playerCurrency -= UpgradeCost;
                increaseAttributes(3, 10, 1, 75);
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



void InfernoTower::setLevelImage() {
    setPixmap(QPixmap(levelImages[UpgradeLevel]).scaled(100,100));
}

void InfernoTower::shoot(){
    emit Tower::shoot(this);
}

//shoot on enemy
void InfernoTower::shoot(Enemy* enemy){
    if(enemy){
        QPointF position = this->pos();
        position.setX(this->x()+50);
        position.setY(this->y()+50);
        Bullet* bullet = new InfernoBullet(map, position, Damage, enemy); //create a new bullet with the specified map, position, damage, and enemy
        bullets.append(bullet); //append the bullet to the list of bullets shot by the tower
        connect(bullet, SIGNAL(deleteBulletSignal(Bullet*)), this, SLOT(handleDeleteBulletSignal(Bullet*)));
    }
}


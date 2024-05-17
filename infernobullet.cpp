#include "infernobullet.h"

InfernoBullet::InfernoBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy)
    : Bullet(map, pos, damage, targetEnemy) {
    // Constructor implementation (if needed)
    this->setPixmap(QPixmap(getImagePath()).scaled(25, 25));
    setBulletSpeed();
}

QString InfernoBullet::getImagePath() const {
    return ":/OtherImages/png-clipart-fire-ball-fire-removebg-preview.png";
}

void InfernoBullet::setBulletSpeed(){
    Bullet::bulletSpeed = 5;
}

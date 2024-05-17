#include "teslabullet.h"

TeslaBullet::TeslaBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy)
    : Bullet(map, pos, damage, targetEnemy) {
    // Constructor implementation (if needed)
    this->setPixmap(QPixmap(getImagePath()).scaled(25, 25)); // Adjust size as needed
    setBulletSpeed();
}

QString TeslaBullet::getImagePath() const {
    return ":/OtherImages/pngtree-electric-ball-or-plasma-sphere-png-image_6035394-removebg-preview.png"; // Return the path to the Tesla bullet image
}

void TeslaBullet::setBulletSpeed(){
    Bullet::bulletSpeed = 4;
}

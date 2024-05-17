#include "xbowbullet.h"

XbowBullet::XbowBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy)
    : Bullet(map, pos, damage, targetEnemy) {
    // Constructor implementation (if needed)
    this->setPixmap(QPixmap(getImagePath()).scaled(20, 20));
    setBulletSpeed();
}

QString XbowBullet::getImagePath() const {
    return ":/OtherImages/stone-transparent-5-removebg-preview.png"; // Return the path to the Xbow bullet image
}

void XbowBullet::setBulletSpeed(){
    Bullet::bulletSpeed = 8;
}

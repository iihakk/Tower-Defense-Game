#include "cannonbullet.h"


CannonBullet::CannonBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy)
    : Bullet(map, pos, damage, targetEnemy) {
    // Constructor implementation (if needed)
    this->setPixmap(QPixmap(getImagePath()).scaled(20, 20));
    setBulletSpeed();
}

//the cannonbullet image
QString CannonBullet::getImagePath() const {
    return ":/OtherImages/Cannonball.png";
}

//sets the bullet's speed
void CannonBullet::setBulletSpeed(){
    Bullet::bulletSpeed = 5;
}

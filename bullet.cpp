#include "bullet.h"
#include <QTimer>

Bullet::Bullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy) {
    this->map = map; // set the map of the bullet (its scene)
    map->addItem(this);

    this->setPos(pos);
    this->setDamage(damage);
    this->enemy = targetEnemy;

    // Create a timer for bullet motion, set the bullet to move every .05 seconds
    bulletMotionTimer = new QTimer();
    connect(bulletMotionTimer, SIGNAL(timeout()), this, SLOT(move()));
    bulletMotionTimer->start(30); // move the bullet 33 times per second
}

Bullet::~Bullet() {
    setEnemy(nullptr);
    bulletMotionTimer->stop();
    if (this->scene() == map) {
        map->removeItem(this);
    }
}

void Bullet::setDamage(int newDamage) {
    damage = newDamage;
}

int Bullet::getDamage() const {
    return damage;
}

Enemy* Bullet::getEnemy() const {
    return enemy;
}

Map* Bullet::getMap() const {
    return map;
}

void Bullet::setEnemy(Enemy* enemy) {
    this->enemy = enemy;
}


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

void Bullet::move() {
    if (enemy == nullptr ||  (!enemy->isALive())){
        delete this;
        return;
    }
    double bulletXPosition = this->x();
    double bulletYPosition = this->y();
    double enemyXPosition = enemy->x();
    double enemyYPosition = enemy->y();

    if (this->pos() != enemy->pos()) {
        if (enemyXPosition > bulletXPosition) {
            this->setX(bulletXPosition + bulletSpeed);
        } else if (enemyXPosition < bulletXPosition) {
            this->setX(bulletXPosition - bulletSpeed);
        }

        if (enemyYPosition > bulletYPosition) {
            this->setY(bulletYPosition + bulletSpeed);
        } else if (enemyYPosition < bulletYPosition) {
            this->setY(bulletYPosition - bulletSpeed);
        }
    }

    QList<QGraphicsItem *> collideItems = collidingItems();
    for (int i = 0; i < collideItems.size(); ++i) {
        Enemy *collidingEnemy= dynamic_cast<Enemy*>(collideItems[i]);
        if (collidingEnemy) {
            this->scene()->removeItem(this);
            enemy->takeDamage(damage); // Inflict damage to the enemy
            emit deleteBulletSignal(this); // Destroy the bullet
            return;
        }
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


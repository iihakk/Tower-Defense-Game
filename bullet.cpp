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
    bulletMotionTimer->start(20); // move the bullet 20 times per second
}

//destructor for the bullet
Bullet::~Bullet() {
    setEnemy(nullptr);
    bulletMotionTimer->stop();
    if (this->scene() == map) {
        map->removeItem(this);
    }
}

//moves the bullet through a simple alogrithm determining the position of the enemy
//also handles the collision between the bullet and the enemies
void Bullet::move() {
    if (enemy == nullptr ||  (!enemy->isALive()) || (enemy->GetMaxHealth()!=100)){
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

//sets the damage to the new damage
void Bullet::setDamage(int newDamage) {
    damage = newDamage;
}

//returns the damage
int Bullet::getDamage() const {
    return damage;
}

//returns the bullet's enemy
Enemy* Bullet::getEnemy() const {
    return enemy;
}

//returns the bullet's map
Map* Bullet::getMap() const {
    return map;
}

//sets the bullet's enemy to the specified enemy
void Bullet::setEnemy(Enemy* enemy) {
    this->enemy = enemy;
}


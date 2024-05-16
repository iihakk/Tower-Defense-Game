#include "infernobullet.h"

InfernoBullet::InfernoBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy)
    : Bullet(map, pos, damage, targetEnemy) {
    // Constructor implementation (if needed)
    this->setPixmap(QPixmap(getImagePath()).scaled(25, 25));
}

void InfernoBullet::move() {
    if (enemy == nullptr ||  (!enemy->isALive()))
        {
            delete this;
            return;
        }
    double bulletXPosition = this->x();
    double bulletYPosition = this->y();
    double enemyXPosition = enemy->x();
    double enemyYPosition = enemy->y();

    if (this->pos() != enemy->pos()) {
        if (enemyXPosition > bulletXPosition) {
            this->setX(bulletXPosition + 2);
        } else if (enemyXPosition < bulletXPosition) {
            this->setX(bulletXPosition - 2);
        }

        if (enemyYPosition > bulletYPosition) {
            this->setY(bulletYPosition + 2);
        } else if (enemyYPosition < bulletYPosition) {
            this->setY(bulletYPosition - 2);
        }
    }
    // Check for collision with the enemy
    if (this->collidesWithItem(enemy)) {
        this->scene()->removeItem(this);
        enemy->takeDamage(damage); // Inflict damage to the enemy
        delete this; // Destroy the bullet
    }
}

QString InfernoBullet::getImagePath() const {
    return ":/OtherImages/png-clipart-fire-ball-fire-removebg-preview.png";
}

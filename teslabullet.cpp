#include "teslabullet.h"

TeslaBullet::TeslaBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy)
    : Bullet(map, pos, damage, targetEnemy) {
    // Constructor implementation (if needed)
    this->setPixmap(QPixmap(getImagePath()).scaled(25, 25)); // Adjust size as needed
}

void TeslaBullet::move() {
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
            this->setX(bulletXPosition + 3); // Adjust speed as needed
        } else if (enemyXPosition < bulletXPosition) {
            this->setX(bulletXPosition - 3); // Adjust speed as needed
        }

        if (enemyYPosition > bulletYPosition) {
            this->setY(bulletYPosition + 3); // Adjust speed as needed
        } else if (enemyYPosition < bulletYPosition) {
            this->setY(bulletYPosition - 3); // Adjust speed as needed
        }
    }
    // Check for collision with the enemy
    if (this->collidesWithItem(enemy)) {
        this->scene()->removeItem(this);
        enemy->takeDamage(damage); // Inflict damage to the enemy
        delete this; // Destroy the bullet
    }
}

QString TeslaBullet::getImagePath() const {
    return ":/OtherImages/pngtree-electric-ball-or-plasma-sphere-png-image_6035394-removebg-preview.png"; // Return the path to the Tesla bullet image
}

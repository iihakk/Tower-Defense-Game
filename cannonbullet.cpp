#include "cannonbullet.h"

CannonBullet::CannonBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy)
    : Bullet(map, pos, damage, targetEnemy) {
    // Constructor implementation (if needed)
    this->setPixmap(QPixmap(getImagePath()).scaled(20, 20));
}

void CannonBullet::move() {
    if (enemy == nullptr ||  (!enemy->isALive())) {
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
}

QString CannonBullet::getImagePath() const {
    return ":/OtherImages/Cannonball.png";
}

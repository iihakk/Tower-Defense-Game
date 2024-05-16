#ifndef CANNONBULLET_H
#define CANNONBULLET_H

#include "bullet.h"

class CannonBullet : public Bullet {
    Q_OBJECT
public:
    CannonBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy);

    void move() override;  // Override the pure virtual function
    QString getImagePath() const override;  // Override the pure virtual function
};

#endif // CANNONBULLET_H

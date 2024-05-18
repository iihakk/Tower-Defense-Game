#ifndef CANNONBULLET_H
#define CANNONBULLET_H

#include "bullet.h"

class CannonBullet : public Bullet {
    Q_OBJECT
public:
    CannonBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy);
    QString getImagePath() const override;  // Override the pure virtual function

protected:
    void setBulletSpeed() override;
};

#endif

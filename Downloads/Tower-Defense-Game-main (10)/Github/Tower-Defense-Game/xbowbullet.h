#ifndef XBOWBULLET_H
#define XBOWBULLET_H

#include "bullet.h"

class XbowBullet : public Bullet {
    Q_OBJECT
public:
    XbowBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy);

    void move() override;  // Override the pure virtual function
    QString getImagePath() const override;  // Override the pure virtual function
};

#endif // XBOWBULLET_H

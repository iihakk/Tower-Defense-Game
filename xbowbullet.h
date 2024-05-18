#ifndef XBOWBULLET_H
#define XBOWBULLET_H

#include "bullet.h"

class XbowBullet : public Bullet {
    Q_OBJECT
public:
    XbowBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy);
    QString getImagePath() const override;  // Override the pure virtual function
protected:
    void setBulletSpeed() override;
};

#endif

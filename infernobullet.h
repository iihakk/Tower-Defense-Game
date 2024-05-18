#ifndef INFERNOBULLET_H
#define INFERNOBULLET_H

#include "bullet.h"

class InfernoBullet : public Bullet {
    Q_OBJECT
public:
    InfernoBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy);
    QString getImagePath() const override; // Override the pure virtual function

protected:
    void setBulletSpeed() override;
};

#endif

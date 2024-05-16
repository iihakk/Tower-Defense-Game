#ifndef INFERNOBULLET_H
#define INFERNOBULLET_H

#include "bullet.h"

class InfernoBullet : public Bullet {
    Q_OBJECT
public:
    InfernoBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy);

    void move() override; // Override the pure virtual function
    QString getImagePath() const override; // Override the pure virtual function
};

#endif // INFERNOBULLET_H

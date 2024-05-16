#ifndef INFERNOBULLET_H
#define INFERNOBULLET_H

#include "bullet.h"

class InfernoBullet : public Bullet {
    Q_OBJECT
public:
    InfernoBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy);

    void move() override;
    QString getImagePath() const override;
};

#endif // INFERNOBULLET_H

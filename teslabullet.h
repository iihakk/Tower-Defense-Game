#ifndef TESLABULLET_H
#define TESLABULLET_H

#include "bullet.h"

class TeslaBullet : public Bullet {
    Q_OBJECT
public:
    TeslaBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy);

    void move() override;  // Override the pure virtual function
    QString getImagePath() const override;  // Override the pure virtual function
};

#endif // TESLABULLET_H

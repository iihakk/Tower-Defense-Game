#ifndef TESLABULLET_H
#define TESLABULLET_H

#include "bullet.h"

class TeslaBullet : public Bullet {
    Q_OBJECT
public:
    TeslaBullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy);
    QString getImagePath() const override;  // Override the pure virtual function
protected:
    void setBulletSpeed() override;

};

#endif

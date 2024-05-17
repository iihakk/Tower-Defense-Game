#ifndef CANNONTOWER_H
#define CANNONTOWER_H

#include "tower.h"
#include "cannonbullet.h"

class CannonTower : public Tower {
public:
    CannonTower(Map* myMap);
    CannonTower(Map* myMap, int posX, int posY);
    bool upgrade(int& playerCurrency) override;
    void setLevelImage() override;
public slots:
    void handleDeleteBulletSignal(Bullet* bullet);

private:
    void shoot() override;
    static const std::vector<QString> levelImages;

};

#endif // CANNONTOWER_H

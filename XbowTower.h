#ifndef XBOWTOWER_H
#define XBOWTOWER_H

#include "tower.h"
#include "xbowbullet.h"

class XbowTower : public Tower {
public:
    XbowTower(Map* map);
    XbowTower(Map* map, int posX, int posY);
    bool upgrade(int& playerCurrency) override;
    void shoot() override;

public slots:
    void handleDeleteBulletSignal(Bullet* bullet);


private:
    void setLevelImage() override;
    static const std::vector<QString> levelImages;
};

#endif // XBOWTOWER_H

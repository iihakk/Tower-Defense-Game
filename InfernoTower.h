#ifndef INFERNOTOWER_H
#define INFERNOTOWER_H

#include "tower.h"
#include "infernobullet.h"

class InfernoTower : public Tower {
public:
    InfernoTower(Map* myMap);
    InfernoTower(Map* myMap, int posX, int posY);
    bool upgrade(int& playerCurrency) override;
    void setLevelImage() override;

public slots:
    void handleDeleteBulletSignal(Bullet* bullet);


private:
    void shoot() override;
    static const std::vector<QString> levelImages;

};

#endif // INFERNOTOWER_H

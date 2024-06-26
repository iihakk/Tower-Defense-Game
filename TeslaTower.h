#ifndef TESLATOWER_H
#define TESLATOWER_H

#include "tower.h"
#include "teslabullet.h"

class TeslaTower : public Tower {
public:
    TeslaTower(Map* map);
    TeslaTower(Map* map, int posX, int posY);
    bool upgrade(int& playerCurrency) override;
    void shoot() override;
    void shoot(Enemy* enemy) override;

signals:
    void shoot(Tower* tower);

public slots:
    void handleDeleteBulletSignal(Bullet* bullet);

private:
    void setLevelImage() override;
    static const std::vector<QString> levelImages;
};

#endif

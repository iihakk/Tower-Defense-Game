#ifndef TESLATOWER_H
#define TESLATOWER_H

#include "tower.h"
#include "teslabullet.h" // Include the Tesla-specific bullet class

class TeslaTower : public Tower {
public:
    TeslaTower(Map* map);
    TeslaTower(Map* map, int posX, int posY);

    bool upgrade(int& playerCurrency) override;
    void shoot() override;

private:
    void setLevelImage() override;
    static const std::vector<QString> levelImages;
};

#endif // TESLATOWER_H

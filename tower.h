#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <vector>
#include "map.h"
#include "enemy.h"
#include "bullet.h"
#include <QMessageBox>

class Tower : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tower(int dmg, int hlth, int cst, int rng, int fireR, Map* map);
    ~Tower();

    virtual bool upgrade(int& playerCurrency) = 0;
    virtual void setLevelImage() = 0;

    QList<Bullet*> bullets;
    QTimer* towerShootingTimer;

    void stopShootingTimer();

    int getlevel();
    int getRange();

    bool upgrademsg();
    void maximumtowerlevel();
    void insufficientbalance();

    virtual void shoot(Enemy* enemy) = 0;
signals:
    void shoot(Tower* tower);

public slots:
    virtual void shoot() = 0;
    void handleDeleteBulletSignal(Bullet* bullet);

protected:
    int Damage;
    int Health;
    int Cost;
    int Range;
    int FiringRate = 100; //firing rate is the number of ms between each bullet
    int UpgradeCost;
    int UpgradeLevel;
    static const int MaxUpgradeLevel = 2;
    bool ConfirmUpgrade;


    Map* map;
    std::vector<QString> levelImages;
    void increaseAttributes(int dmgIncrease, int rangeIncrease, int rateIncrease, int costIncrease);

};

#endif

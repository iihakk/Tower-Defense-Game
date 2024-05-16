#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <vector>
#include "map.h"
#include "enemy.h"
#include "cannonbullet.h"
#include "infernobullet.h"

class Tower : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tower(int dmg, int hlth, int cst, int rng, int fireR, Map* map);
    ~Tower();
    virtual bool upgrade(int& playerCurrency) = 0;
    virtual void setLevelImage() = 0;
    void setClosestEnemy(Enemy* enemy);
    void setEnemies(QList<Enemy*>& enemies);
    Enemy* getClosestEnemy() const;
    QList<Bullet*> bullets;
    QTimer* towerShootingTimer;
    void stopShootingTimer();

public slots:
    virtual void shoot() = 0;

protected:
    int Damage;
    int Health;
    int Cost;
    int Range;
    int FiringRate = 100; //firing rate is the number of ms between each bullet
    int UpgradeCost;
    int UpgradeLevel;
    static const int MaxUpgradeLevel = 3;
    Enemy* closestEnemy;
    QList<Enemy*> enemies;

    Map* map;
    std::vector<QString> levelImages;
    void increaseAttributes(int dmgIncrease, int rangeIncrease, int rateIncrease, int costIncrease);

    double calculateDistance(const QPointF& from, const QPointF& to);
    Enemy* findClosestEnemyWithinRange();
};

#endif // TOWER_H

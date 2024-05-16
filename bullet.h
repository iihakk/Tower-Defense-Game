#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "map.h"
#include "enemy.h"

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(Map* map, QPointF& pos, double damage, Enemy* targetEnemy);
    virtual ~Bullet();

    void setDamage(int damage);
    int getDamage() const;
    void setEnemy(Enemy* enemy);
    Enemy* getEnemy() const;
    Map* getMap() const;

    // Pure virtual function to get the image path
    virtual QString getImagePath() const = 0;

public slots:
    virtual void move() = 0;  // Pure virtual function to make the class abstract

protected:
    Map* map;
    Enemy* enemy;
    double damage;
    QTimer* bulletMotionTimer;
};

#endif // BULLET_H

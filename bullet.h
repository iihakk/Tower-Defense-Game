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
    void setEnemy(Enemy* enemy);
    Enemy* getEnemy() const;

    // Pure virtual function to get the image path
    virtual QString getImagePath() const = 0;
signals:
    void deleteBulletSignal(Bullet* bullet);

public slots:
    virtual void move();  // Pure virtual function to make the class abstract

protected:
    Map* map;
    Enemy* enemy{};
    double damage;
    QTimer* bulletMotionTimer;
    int bulletSpeed = 2; //default value

    virtual void setBulletSpeed() = 0;

};

#endif

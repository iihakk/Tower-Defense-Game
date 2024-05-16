#ifndef MAP_H
#define MAP_H
#include <QGraphicsScene>
#include <QObject>
#include <vector>
#include <QLabel>
#include <QPushButton>

class Map : public QGraphicsScene
{
    Q_OBJECT
private:
    int width = 1400;
    int height = 700;
    double enemySpeed = 2.5;
    double health;
    int level;

    QPushButton *shopbutton;
    QPushButton *upgradebutton;

    QLabel* lblHealth;
    QLabel* lblLevel;
    QLabel* lblCoins;

    void createPath(int level);
    void createTiles();

    void getPath(double& targetCoordinate, double& currentIndexX, double& currentIndexY,  bool isOnXAxis);
    void getPath(double& targetCoordinate, double& currentIndexX, double& currentIndexY,  bool v2, bool isOnXAxis);
    void findPath(double& enemySpeed, double& targetCoordinate, double &indexX, double &indexY, bool isOnXAxis);

public:
    Map(int level);
    void startScene();

    void setHealthLabelText(int num);
    void setLevelLabelText(int num);
    void setCoinsLabelText(int num);
    void showShop();

    int Coins;

    int getcoinbalance();

    void setEnemySpeed(double numPixelsPerMove);

    std::vector<QPoint*> path;
    std::vector<QPoint*> path2;
    std::vector<QGraphicsRectItem*> tiles;

signals:
    void deploythecannon();
    void deploythetesla();
    void deploythexbow();
    void deploytheinferno();
    void upgradetower();
};

#endif // MAP_H

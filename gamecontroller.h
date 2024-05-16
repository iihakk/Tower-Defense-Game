#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QList>
#include "map.h"
#include "enemy.h"
#include "cannontower.h"
#include "infernotower.h"
#include "xbowtower.h"
#include "teslatower.h"
#include "QMediaPlayer"
#include "QSoundEffect"

class GameController : public QObject
{
    Q_OBJECT

public:
    GameController(Map* map);

    void setTotalWaves(int totalWaves);

signals:
    void playerLost(); // Declaration of the playerLost signal

public slots:
    void spawnWave();
    void startWaves();

private:
    Map* map;
    QList<Enemy*> enemies;
    // QList<CannonTower*> towers;
    QList<Tower*> towers;
    QTimer* waveTimer;
    int currentWaveIndex;
    int totalWaves;
    int numEnemiesPerWave;
    int waveInterval;
    int waveDuration;
    int playerHealth; // Declaration of playerHealth variable
    int coinbalance;
    int selectedtower;

    QSoundEffect* BalloonSpawn;
    QSoundEffect* BalloonDie;
    QSoundEffect* UpgradeSound;

    void spawnEnemy();
    void handleEnemyDestroyed(Enemy* destroyedEnemy);
    void handleEnemyDissapeared(Enemy* enemy);
    void handlePlayerLost();

    void placexbow();
    void placetesla();
    void placeinferno();
    void placecannon();

    void UpgradeTower();
    bool towerbuilt(int x,int y);

};

#endif // GAMECONTROLLER_H


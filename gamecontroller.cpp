#include "gamecontroller.h"
#include <QMouseEvent>
#include <iostream>
#include <QMessageBox>

GameController::GameController(Map* map)
    : QObject(),
    currentWaveIndex(0),
    totalWaves(2),
    numEnemiesPerWave(5),
    waveInterval(5000),
    waveDuration(10000),
    playerHealth(100), // Initialize playerHealth with an initial value
    coinbalance(1000) //initialize coin balance
{
    this->map = map;
    BalloonSpawn = new QSoundEffect(this);
    BalloonSpawn->setSource(QUrl("qrc:/Effects/BalloonSpawn.wav"));
    BalloonDie = new QSoundEffect(this);
    BalloonDie->setSource(QUrl("qrc:/Effects/BalloonDie.wav"));
    waveTimer = new QTimer(this);
    connect(waveTimer, &QTimer::timeout, this, &GameController::startWaves);
    waveTimer->start(waveInterval);

    connect(this, &GameController::playerLost, this, &GameController::handlePlayerLost);

    //timer to check if a tower has been added (if a tile was clicked)
    QTimer* checkIfAddTowerTimer = new QTimer(this);
    connect(checkIfAddTowerTimer, &QTimer::timeout, this, &GameController::handleTileSelected);
    checkIfAddTowerTimer->start(10);
}

//sets the number of waves
void GameController::setTotalWaves(int totalWaves)
{
    this->totalWaves = totalWaves;
}

//spawns a wave of enemies
void GameController::spawnWave()
{
    if (currentWaveIndex >= totalWaves) {
        waveTimer->stop();
        return;
    }

    for (int i = 0; i < numEnemiesPerWave; i++) {
        QTimer::singleShot(i * (waveDuration / numEnemiesPerWave), this, &GameController::spawnEnemy);
    }

    currentWaveIndex++;
}

//starts the waves
void GameController::startWaves()
{
    spawnWave();
    waveTimer->start(waveInterval + waveDuration);
}

//spawns an enemy into existence
void GameController::spawnEnemy()
{
    BalloonSpawn->play();
    Enemy *enemy = new Enemy(map);
    enemies.append(enemy);

    connect(enemy, &Enemy::enemyDestroyed, this, &GameController::handleEnemyDestroyed);
    connect(enemy, &Enemy::enemyDissapeared, this, &GameController::handleEnemyDissapeared);

    for(int i =0 ; i< towers.size(); i++){
        towers[i]->setEnemies(enemies);
    }
}

//if an enemy is destroyed, remove the enemy and all the bullets that headed towards the now dead enemy
void GameController::handleEnemyDestroyed(Enemy* destroyedEnemy) {
    if (destroyedEnemy) {
        BalloonDie->play();
        // increase coin balance
        coinbalance += 150;
        map->setCoinsLabelText(coinbalance);

        enemies.removeOne(destroyedEnemy);

        for(int i =0 ; i< towers.size(); i++){
            towers[i]->setEnemies(enemies);
        }

        for(int i = 0; i < towers.size(); i++){
            for(int j = 0; j < towers[i]->bullets.size(); j++){
                Bullet* b = towers[i]->bullets[j];
                if (b){
                if(b->getEnemy() == destroyedEnemy){
                    if(towers[i]->scene() == b->scene()){
                       // towers[i]->bullets.removeOne(b);
                        delete b;
                    }}
                }
            }
        }
        delete destroyedEnemy;
    }
}

//if an enemy dissapeared, remove the enemy and decrease the player health
void GameController::handleEnemyDissapeared(Enemy* enemy){
    enemies.removeOne(enemy);
    for(int i =0 ; i< towers.size(); i++){
        towers[i]->setEnemies(enemies);
    }
    playerHealth -= 10;
    map->setHealthLabelText(playerHealth);
    if(playerHealth <= 0){
        emit playerLost();
    }
    delete enemy;
}

void GameController::handlePlayerLost(){

    QMessageBox * msg = new QMessageBox();
    msg->setWindowTitle("GAME OVER");
    msg->setText("GAME OVER");
    msg->show();

    // close the game
}

// void GameController::handleTileSelected(){
//     for(QGraphicsRectItem* tile: map->tiles){
//         if(tile->isSelected()){
//             CannonTower* newCannon = new CannonTower(map, tile->x(),tile->y());
//             towers.append(newCannon);
//             tile->setFlag(QGraphicsItem::ItemIsSelectable, false);
//         }
//     }
// }


// void GameController::handleTileSelected(){
//     for(QGraphicsRectItem* tile: map->tiles){
//         if(tile->isSelected()){
//             InfernoTower* newInferno = new InfernoTower(map, tile->x(), tile->y());
//             towers.append(newInferno);
//             tile->setFlag(QGraphicsItem::ItemIsSelectable, false);
//         }
//     }
// }

void GameController::handleTileSelected(){
    for(QGraphicsRectItem* tile: map->tiles){
        if(tile->isSelected()){
            XbowTower* newXbow = new XbowTower(map, tile->x(), tile->y());
            towers.append(newXbow);
            tile->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
    }
}

// void GameController::handleTileSelected(){
//     for(QGraphicsRectItem* tile: map->tiles){
//         if(tile->isSelected()){
//             TeslaTower* newTesla = new TeslaTower(map, tile->x(), tile->y());
//             towers.append(newTesla);
//             tile->setFlag(QGraphicsItem::ItemIsSelectable, false);
//         }
//     }
// }






#include "gamecontroller.h"
#include <QMouseEvent>
#include <iostream>
#include <QMessageBox>
#include <QApplication> // Add this include
#include <QGraphicsView>

//constructor
GameController::GameController(Map* map, int mapLevel, QGraphicsView* view)
    : QObject(),
    currentWaveIndex(0)
{
    this->map = map;
    this->view = view;

    //initialization of the initial variables according based on the map levels
    this->mapLevel = mapLevel;
    numEnemiesPerWave = 5+((this->mapLevel*5)/2);
    waveDuration = 10000 + 1000*mapLevel;
    totalWaves = ((this->mapLevel) == 1)?2:(this->mapLevel);
    playerHealth = 100;
    coinbalance = 600+400*(this->mapLevel);
    waveInterval = 10000 + 1000 * mapLevel;
    numFinishedEnemies = totalWaves*numEnemiesPerWave;

    //display the changes on the scene (the map)
    map->setCoins(coinbalance);
    map->setHealth(playerHealth);

    //sound effects
    BalloonSpawn = new QSoundEffect(this);
    BalloonSpawn->setSource(QUrl("qrc:/Effects/BalloonSpawn.wav"));

    BalloonDie = new QSoundEffect(this);   
    BalloonDie->setSource(QUrl("qrc:/Effects/BalloonDie.wav"));
    waveTimer = new QTimer(this);

    UpgradeSound = new QSoundEffect(this);
    UpgradeSound->setSource(QUrl("qrc:/Effects/UpgradeSound.wav"));

    //connect
    connect(waveTimer, &QTimer::timeout, this, &GameController::startWaves);
    waveTimer->start(waveInterval);

    //connect
    connect(this, &GameController::playerLost, this, &GameController::handlePlayerLost);

    // catch signals if sent to place towers and call each ones function
    connect(map, &Map :: deploythexbow, this, &GameController :: placexbow);
    connect(map, &Map :: deploytheinferno, this, &GameController :: placeinferno);
    connect(map, &Map :: deploythecannon, this, &GameController :: placecannon);
    connect(map, &Map :: deploythetesla, this, &GameController :: placetesla);


    connect(map, &Map :: upgradetower, this, &GameController :: UpgradeTower);
}

//sets the number of waves
void GameController::setTotalWaves(int totalWaves)
{
    this->totalWaves = totalWaves;
}

//spawns a wave of enemies
void GameController::spawnWave()
{
    if (currentWaveIndex >= totalWaves || playerHealth <= 0) {
        waveTimer->stop();
        return;
    }

    if (playerHealth > 0) {
        for (int i = 0; i < numEnemiesPerWave; i++) {
            QTimer::singleShot(i * (waveDuration / numEnemiesPerWave), this, &GameController::spawnEnemy);
        }
    }

    currentWaveIndex++;
}

//starts the waves
void GameController::startWaves()
{
    if (playerHealth > 0) {
        spawnWave();
        waveTimer->start(waveInterval + waveDuration);
    }
}

//spawns an enemy into existence
void GameController::spawnEnemy()
{
    if (playerHealth > 0) {
        BalloonSpawn->play();
        Enemy *enemy = new Enemy(map);
        enemies.append(enemy);

        connect(enemy, &Enemy::enemyDestroyed, this, &GameController::handleEnemyDestroyed);
        connect(enemy, &Enemy::enemyDissapeared, this, &GameController::handleEnemyDissapeared);
    }
}

//if an enemy is destroyed, remove the enemy and all the bullets that headed towards the now dead enemy
void GameController::handleEnemyDestroyed(Enemy* destroyedEnemy) {
    if (destroyedEnemy) {
        if (!BalloonDie->isPlaying()) {
            BalloonDie->play();
        }
        // increase coin balance
        coinbalance += 150;
        map->setCoinsLabelText(coinbalance);

        numFinishedEnemies--;
        enemies.removeOne(destroyedEnemy);

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
    if(numFinishedEnemies == 0 || numFinishedEnemies == -1){
        nextLevel();
    }
}

//if an enemy dissapeared, remove the enemy and decrease the player health
void GameController::handleEnemyDissapeared(Enemy* enemy){
    enemy->setAlive(false);
    numFinishedEnemies--;
    enemies.removeOne(enemy);
    playerHealth -= 10;
    map->setHealthLabelText(playerHealth);
    if(playerHealth <= 0){
        waveTimer->stop();
        emit playerLost();
    }
    delete enemy;

    if(numFinishedEnemies == 0 || numFinishedEnemies == -1){
        nextLevel();
    }
}

//if the player lost, show a button to try again or quit
void GameController::handlePlayerLost(){
    waveTimer->stop();
    disconnect(this, &GameController::playerLost, this, &GameController::handlePlayerLost);
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
    QMessageBox msgBox;
    msgBox.setWindowTitle("GAME OVER");
    msgBox.setText("GAME OVER");

    QPushButton *tryAgainButton = msgBox.addButton(tr("Try Again"), QMessageBox::ActionRole);
    QPushButton *quitButton = msgBox.addButton(tr("Quit"), QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == tryAgainButton) {
        resetLevel();
    } else if (msgBox.clickedButton() == quitButton) {
        closeGame();
    }
}

//resets the current level
void GameController::resetLevel() {
    for (Tower* tower : towers) {
        delete tower;
    }
    towers.clear();
    playerHealth = 100;
    map->setHealthLabelText(playerHealth);
    coinbalance = 1000+400*(this->mapLevel);
    map->setCoinsLabelText(coinbalance);
    currentWaveIndex = 0;

    GameController* newGameController = new GameController(map,mapLevel, view);
    QObject::connect(newGameController, &GameController::playerLost, this, &GameController::handlePlayerLost);

    deleteLater(); // Delete the current GameController instance
}

//shows message box to create a new level
void GameController::nextLevel(){
    int newLevel = mapLevel+1;
    if(newLevel > 5){
        QMessageBox msgBox;
        msgBox.setWindowTitle("THE CONQUERER");
        msgBox.setText("CONQUERED EARTH");

        QPushButton *tryAgainButton = msgBox.addButton(tr("Reconquer"), QMessageBox::ActionRole);
        QPushButton *quitButton = msgBox.addButton(tr("Quit"), QMessageBox::RejectRole);

        msgBox.exec();

        if (msgBox.clickedButton() == tryAgainButton) {
            resetLevel();
        } else if (msgBox.clickedButton() == quitButton) {
            closeGame();
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("THE CONQUERER");
        msgBox.setText("CONQUERED THIS LEVEL");

        QPushButton *nextLevel = msgBox.addButton(tr("Next Level"), QMessageBox::ActionRole);
        QPushButton *playAgainButton= msgBox.addButton(tr("Play Again"), QMessageBox::ActionRole);
        QPushButton *quitButton = msgBox.addButton(tr("Quit"), QMessageBox::RejectRole);

        msgBox.exec();

        if(msgBox.clickedButton() == nextLevel){
            startNextLevel(newLevel);
        }
        else if (msgBox.clickedButton() == playAgainButton) {
            resetLevel();
        } else if (msgBox.clickedButton() == quitButton) {
            closeGame();
        }
    }
}

//starts the next level
void GameController::startNextLevel(int newLevel){
    if(newLevel > 5){
        return;
    }
    Map* newMap = new Map(newLevel);
    view->setScene(newMap);
    GameController* newGameController = new GameController(newMap, newLevel, view);

    deleteLater();
}

//closes the game
void GameController::closeGame() {
    QApplication::quit();
}

//places a cannon on the specified tile
void GameController::placecannon(){

    for(QGraphicsRectItem* tile: map->tiles){
        if(tile->isSelected() && (towerbuilt(tile->x(),tile->y()) == false)){

            // remove coins to buy the tower
            coinbalance -= 500;
            map->setCoins(coinbalance);
            map->setCoinsLabelText(coinbalance);
            UpgradeSound->play();
            CannonTower* newCannon = new CannonTower(map, tile->x(),tile->y());
            towers.append(newCannon);
            connect(newCannon, SIGNAL(shoot(Tower*)), this, SLOT(handleTowerShooting(Tower*)));
            //tile->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
    }
}

//upgrades a tower
void GameController::UpgradeTower()
{

    for(QGraphicsRectItem* tile: map->tiles){
        if(tile->isSelected() && towerbuilt(tile->x(),tile->y())){

            if (towers[selectedtower]->getlevel() == 2){
                towers[selectedtower]->maximumtowerlevel();
            }
                else if (towers[selectedtower]->upgrade(coinbalance) == true){
                    UpgradeSound->play();
                    map->setCoinsLabelText(coinbalance);
                }
        }
    }
}

//returns true if a tower has been built on the specified location
bool GameController::towerbuilt(int x, int y)
{

    QPointF point(x,y);

    for (int i = 0; i <towers.size();i++){
        if (towers[i]->pos() == point){

            selectedtower = i;
            return true;

        }
    }
    return false;
}

//places an inferno tower
void GameController::placeinferno(){

    for(QGraphicsRectItem* tile: map->tiles){
        if(tile->isSelected() && (towerbuilt(tile->x(),tile->y()) == false)){

            // remove coins to buy the tower
            coinbalance -= 1500;
            map->setCoins(coinbalance);
            map->setCoinsLabelText(coinbalance);
            UpgradeSound->play();

            InfernoTower* newInferno = new InfernoTower(map, tile->x(), tile->y());
            towers.append(newInferno);
            connect(newInferno, SIGNAL(shoot(Tower*)), this, SLOT(handleTowerShooting(Tower*)));
        }
    }
}

//places an xbow tower
void GameController::placexbow(){

    for(QGraphicsRectItem* tile: map->tiles){
        if(tile->isSelected() && (towerbuilt(tile->x(),tile->y()) == false)){
            // remove coins to buy the tower
            coinbalance -= 1000;
            map->setCoins(coinbalance);
            map->setCoinsLabelText(coinbalance);
            UpgradeSound->play();
            XbowTower* newXbow = new XbowTower(map, tile->x(), tile->y());
            towers.append(newXbow);
            connect(newXbow, SIGNAL(shoot(Tower*)), this, SLOT(handleTowerShooting(Tower*)));
        }
    }
}

//places a tesla tower
void GameController::placetesla(){
    for(QGraphicsRectItem* tile: map->tiles){
        if(tile->isSelected() && (towerbuilt(tile->x(),tile->y()) == false)){

            //remove coins to buy the tower
            coinbalance -= 750;
            map->setCoins(coinbalance);
            map->setCoinsLabelText(coinbalance);
            UpgradeSound->play();

            TeslaTower* newTesla = new TeslaTower(map, tile->x(), tile->y());
            towers.append(newTesla);
            connect(newTesla, SIGNAL(shoot(Tower*)), this, SLOT(handleTowerShooting(Tower*)));
        }
    }
}

//Calculate the distance between two points
double GameController::calculateDistance(const QPointF& from, const QPointF& to) {
    return sqrt(pow(from.x() - to.x(), 2) + pow(from.y() - to.y(), 2));
}

//Find the closest enemy within range
Enemy* GameController::findClosestEnemyWithinRange(Tower* tower){

    //Set the closest enemy to be at infinite distance
    double closestEnemyDistance = INT_MAX;
    int indexClosestEnemy = -1;
    double currentDistance = INT_MAX;
    for(int i = 0; i < enemies.size();i++){
        if(enemies[i]->scene() == map){
            QPointF enemyPos = enemies[i]->pos();
            currentDistance = calculateDistance(enemyPos, tower->pos());
            if(currentDistance <= tower->getRange() && currentDistance < closestEnemyDistance){ //If the enemy is closer than the closest enemy and within range update the closest
                closestEnemyDistance = currentDistance;
                indexClosestEnemy = i;
            }
        }
    }

    if(indexClosestEnemy == -1){
        return nullptr;
    }

    if(enemies[indexClosestEnemy]){
        return enemies[indexClosestEnemy];
    }

    return nullptr;
}

//allows the tower to shoot at the closest enemy
void GameController::handleTowerShooting(Tower* tower){
    Enemy* closestEnemy = findClosestEnemyWithinRange(tower);
    if(closestEnemy)
        tower->shoot(closestEnemy);
}



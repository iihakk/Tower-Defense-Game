#include "Enemy.h"
#include "QTimer"
#include "QAudioOutput"
#include "QGraphicsScene"
#include "QGraphicsProxyWidget"
#include "Bullet.h"
#include "QGraphicsProxyWidget"
using namespace std;

// Constructor of the enemy
Enemy::Enemy(Map* map) : QObject(), QGraphicsPixmapItem() {
    health = 100;
    maxHealth = 100;
    isAlive = true;

    setPixmap(QPixmap(":/OtherImages/Enemy_Dropper_Ballon.png").scaled(79, 100));

    motionTimer = new QTimer();
    connect(motionTimer, SIGNAL(timeout()), this, SLOT(move()));
    motionTimer->start(50);

    this->map = map;

    // Add the enemy to the map and set its position to the starting point in the path
    map->addItem(this);

    healthBar.setMinimum(0);
    healthBar.setMaximum(100);
    healthBar.setValue(health);

    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(&healthBar);
    proxy->setScale(0.3);
    proxy->setRotation(0);
    proxy->setPos(0, -10);
    proxy->setParentItem(this);

    // Set initial color of the health bar
    setHealthBarColor("green");

    //determine the path of the enemy (some maps have more than one path) by a random assignment
    if(map->path2.size() == 1){ // no alternate in existence
        enemyPath = map->path;
    }
    else{
        srand(time(0));
        int rand = std::rand()%2;
        (rand == 0) ? (enemyPath = map->path) : (enemyPath = map->path2);
    }
    // set the position to the first position on the path
    this->setX(enemyPath[0]->x());
    this->setY(enemyPath[0]->y());
}

// Destructor of the enemy
Enemy::~Enemy() {
    // Remove the enemy from the map
    if(this->scene() == map){
        map->removeItem(this);
    }
}

void Enemy::move() {
    // If the enemy has passed the whole path
    if(currentIndex+1 == enemyPath.size()){
        motionTimer->stop(); // Stop the timer
        // Emit the enemyDissapeared signal to be handled by the appropriate function (decrease player health)
        emit enemyDissapeared(this);
        return;
    }
    // Set position to next point on path
    this->setX(enemyPath[currentIndex]->x());
    this->setY(enemyPath[currentIndex++]->y());
}

void Enemy::takeDamage(int damage) {
    health -= damage;
    // Ensure health doesn't go below 0
    if (health < 0) {
        health = 0;
    }
    // Update the health bar value
    updateHealthBar();

    if (health <= 0) {
        isAlive = false;
        emit enemyDestroyed(this);
    }
}

void Enemy::updateHealthBar() {
    // Update the health bar value
    healthBar.setValue(health);
    // Trigger a repaint to ensure the health bar is updated visually
    if (scene())
        scene()->update();
}

void Enemy::setHealthBarColor(const QString& color) {
    // Set the stylesheet to change the color of the health bar
    healthBar.setStyleSheet("QProgressBar::chunk { background-color: " + color + "; }");
}

// Returns enemy health
int Enemy::getHealth() const {
    return health;
}

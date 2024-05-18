#include "map.h"
#include <QtWidgets/QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QFont>
#include <QObject>
#include <QDebug>
#include <shop.h>

//Initialize the map
Map::Map(int level) {
    // initialize health, score and level variables with correct values
    this->level = level;
    health = 100;
    Coins =1000;
    QGraphicsScene();
    startScene();
}


//Function that starts the scene with all its attribtues
void Map::startScene(){

    //Set a constant scene rectangle to avoid having the scene moving
    this->setSceneRect(0,0,width,height);

    //Initialize the path
    createPath(level);

    //Create a background Image
    QPixmap backgroundImage(":/OtherImages/dark-rock-wall-seamless-texture-free-105.jpg.png");
    backgroundImage.scaled(this->width, this->height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->setBackgroundBrush(backgroundImage);


    // initialize shop button
    shopbutton = new QPushButton("Shop");


    // add it to the scene
    QGraphicsProxyWidget *shoppushbutton = this->addWidget(shopbutton);

    QFont font("Arial", 20);

    connect(shopbutton, &QPushButton::clicked, this, &Map ::showShop);

    shoppushbutton->setFont(font);

    // place button in correct position
    shoppushbutton->setGeometry(QRectF(1200,100,200,100));

    // initialize upgrade button
    upgradebutton = new QPushButton("Upgrade");

    // add it to the scene
    QGraphicsProxyWidget *upgrade = this->addWidget(upgradebutton);

    connect(upgradebutton, &QPushButton::clicked, this, &Map :: upgradetower);

    upgrade->setFont(font);

    upgrade->setGeometry(QRectF(1200,200,200,100));

    //make labels for health, coins and Level
    lblHealth = new QLabel();
    lblCoins = new QLabel();
    lblLevel = new QLabel();

    QGraphicsProxyWidget *healthlabel = this->addWidget(lblHealth);
    QGraphicsProxyWidget *coinslabel = this->addWidget(lblCoins);
    QGraphicsProxyWidget *levellabel = this->addWidget(lblLevel);

    healthlabel->setFont(font);
    coinslabel->setFont(font);
    levellabel->setFont(font);

    // place labels in correct position
    levellabel->setGeometry(QRectF(700,50,20,10));
    healthlabel->setGeometry(QRectF(5,0,20,10));
    coinslabel->setGeometry(QRectF(5,50,150,10));

    // initialize health, score and level labels with correct values
    setHealthLabelText(health);
    setLevelLabelText(level);
    setCoinsLabelText(Coins);

    createTiles();
}

void Map::createTiles(){

    QGraphicsRectItem* rectItem; //rect item to initialize the tiles

    QBrush myBrush(Qt::transparent); //Set all tiles to be transparent
    QBrush pathBrush(QPixmap(":/OtherImages/Sand.png").scaled(60,100)); //Set only the path tiles to have a sand background

    //Create 100x100 tiles
    for(int i = 0; i < width; i+=100){
        for(int j = 0; j < height; j+=100){

            if (!((i >= 1200 && i <= 1300) && (j >= 100 && j <= 200))) {
            rectItem = new QGraphicsRectItem(0,0,100,100); //create a new tile

            //fix its position
            rectItem->setX(i);
            rectItem->setY(j);

            //set its brush to transparent and visible
            rectItem->setBrush(myBrush);
            rectItem->setVisible(true);

            //Make it selectable to be able to add towers
            rectItem->setFlag(QGraphicsItem::ItemIsSelectable, true);

            tiles.push_back(rectItem); //Add the tile to the tile list
            this->addItem(rectItem); //Add the tile to the map

            for(size_t k = 0; k< path.size(); k++){

                //check if the tile is on the path, if yes...
                if(((i - path[k]->x()) > -100 && (i - path[k]->x()) < 100) && ((j - path[k]->y()) > -100 && (j - path[k]->y()) <100)){
                    //.. make it impossible to put a tower on it and make its background sandy
                    rectItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    rectItem->setBrush(pathBrush);
                    break;
                }
            }
            if(path2.size() != 1 && path2.size() != 0){
            for(size_t k = 0; k< path2.size(); k++){

                //check if the tile is on the path, if yes...
                if(((i - path2[k]->x()) > -100 && (i - path2[k]->x()) < 100) && ((j - path2[k]->y()) > -100 && (j - path2[k]->y()) <100)){
                    //.. make it impossible to put a tower on it and make its background sandy
                    rectItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    rectItem->setBrush(pathBrush);
                    break;
                }
            }
            }
            }
        }
    }
}

void Map::setHealth(double newHealth)
{
    health = newHealth;
    setHealthLabelText(health);
}

//Creates a path of tiles on which the enemies will move
void Map::setCoins(int newCoins)
{
    Coins = newCoins;
    setCoinsLabelText(Coins);
}

int Map::getCoins() const
{
    return Coins;
}

void Map::createPath(int level){
    //an extra check to ensure that both paths do not contain already created code
    if(!path.empty()){
        while(!path.empty()){
            path.pop_back();
        }
    }
    if(!path2.empty()){
        while(!path2.empty()){
            path2.pop_back();
        }
    }

    path2.push_back(new QPoint(-1,-1)); //mark path2 as nonexistent by default

    //Create the path for level 1
    if(level == 1){

        //The shift points, the enemy will keep moving until it reaches them, then shifts
        double shift1Y = 500, shift1X = 700, shift2Y = 300, shift2X = 400;
        double endpoint = -100; //adjusted to the height of the enemy (100 pixels)

        double indexX = this->width/2;
        double indexY = this->height;
        while(indexY > shift1Y){
            getPath(shift1Y, indexX, indexY, false);
        }
        while(indexX < shift1X){
            getPath(shift1X, indexX, indexY, true);
        }
        while(indexY > shift2Y){
            getPath(shift2Y, indexX, indexY, false);
        }
        while(indexX > shift2X){
            getPath(shift2X, indexX, indexY, true);
        }
        while(indexY >= endpoint){
            getPath(endpoint, indexX, indexY, false);
        }

    }

    else if(level == 2){
        //The shift points, the enemy will keep moving until it reaches them, then shifts
        double shift1Y = 400, shift1X = 200, shift2Y = 100, shift2X = 1000;
        double endpoint = -100; //adjusted to the height of the enemy (100 pixels)

        double indexX = this->width/2 - 100;
        double indexY = this->height;

        while(indexY > shift1Y){
            getPath(shift1Y, indexX, indexY, false);

        }
        while(indexX > shift1X){
            getPath(shift1X, indexX, indexY, true);

        }
        while(indexY > shift2Y){
            getPath(shift2Y, indexX, indexY, false);
        }
        while(indexX < shift2X){
            getPath(shift2X, indexX, indexY, true);
        }
        while(indexY >= endpoint){
            getPath(endpoint, indexX, indexY, false);
        }
    }

    else if(level == 3){
        //The shift points, the enemy will keep moving until it reaches them, then shifts
        double shift1Y = 600, shift1X = 500, shift2Y = 0, shift2X = 1100;
        double endpoint = 1500; //adjusted to the height of the enemy (100 pixels) (here, on the x-axis)

        double indexX = 0;
        double indexY = 100;

        while(indexX < shift1X){
            getPath(shift1X, indexX, indexY, true);
        }
        while(indexY < shift1Y){
            getPath(shift1Y, indexX, indexY, false);

        }
        while(indexX < shift2X){
             getPath(shift2X, indexX, indexY, true);

        }
        while(indexY > shift2Y){
             getPath(shift2Y, indexX, indexY, false);
        }
        while(indexX < endpoint){
             getPath(endpoint, indexX, indexY, true);

        }
    }

    //this level has two paths so it initializes path1 and path2 as opposite yet identical paths
    else if(level == 4){
        path2.pop_back(); // remove the no path2 in existence marker

        //The shift points, the enemy will keep moving until it reaches them, then shifts
        double shift1Y = 200, shift1X = 100, shift2Y = 600, shift2X = 1200;
        double endpoint = 1500; //adjusted to the height of the enemy (100 pixels) (here, on the x-axis)

        double indexX = 0;
        double indexY = this->height-100;

        while(indexX < shift1X){
            getPath(shift1X, indexX, indexY, true);
        }
        while(indexY > shift1Y){
            getPath(shift1Y, indexX, indexY, false);

        }
        while(indexX < shift2X){
            getPath(shift2X, indexX, indexY, true);

        }
        while(indexY < shift2Y){
            getPath(shift2Y, indexX, indexY, false);
        }
        while(indexX < endpoint){
            getPath(endpoint, indexX, indexY, true);

        }

        //The shift points, the enemy will keep moving until it reaches them, then shifts
        shift1Y = 200, shift1X = 1200, shift2Y = 600, shift2X = 100;
        endpoint = -100; //adjusted to the height of the enemy (100 pixels) (here, on the x-axis)

        indexX = 1400;
        indexY = 600;

        while(indexX > shift1X){
            getPath(shift1X, indexX, indexY,true, true);
        }
        while(indexY > shift1Y){
            getPath(shift1Y, indexX, indexY, true, false);

        }
        while(indexX > shift2X){
            getPath(shift2X, indexX, indexY, true, true);

        }
        while(indexY < shift2Y){
            getPath(shift2Y, indexX, indexY, true, false);
        }
        while(indexX > endpoint){
            getPath(endpoint, indexX, indexY, true, true);

        }
    }

    else if (level == 5){
        path2.pop_back(); // remove the no path2 in existence marker

        //The shift points, the enemy will keep moving until it reaches them, then shifts
        double shift1Y = 500, shift1X = 1000, shift2Y = 100, shift2X = 300;
        double endpoint = -100; //adjusted to the height of the enemy (100 pixels) (here, on the y-axis)

        double indexX = width/4-50;
        double indexY = height-100;


        while(indexY > shift1Y){
            getPath(shift1Y, indexX, indexY, false);
        }
        while(indexX < shift1X){
            getPath(shift1X, indexX, indexY, true);
        }
        while(indexY > shift2Y){
            getPath(shift2Y, indexX, indexY, false);
        }
        while(indexX > shift2X){
            getPath(shift2X, indexX, indexY, true);

        }
        while(indexY > endpoint){
            getPath(endpoint, indexX, indexY, false);
        }

        //The shift points, the enemy will keep moving until it reaches them, then shifts
        shift1Y = 500, shift1X = 100, shift2Y = 200;
        endpoint = -100; //adjusted to the height of the enemy (100 pixels) (here, on the x-axis)

        indexX = width/2;
        indexY = height-100;

        while(indexY > shift1Y){
            getPath(shift1Y, indexX, indexY, true, false);
        }
        while(indexX > shift1X){
            getPath(shift1X, indexX, indexY,true, true);
        }
        while(indexY > shift2Y){
            getPath(shift2Y, indexX, indexY, true, false);
        }
        while(indexX > endpoint){
            getPath(endpoint, indexX, indexY, true, true);
        }
    }

}

//helper function to create new point on the path
void Map::getPath(double& targetCoordinate, double& currentIndexX, double& currentIndexY, bool isOnXAxis){
    QPoint* currentPoint = new QPoint();
    currentPoint->setX(currentIndexX);
    currentPoint->setY(currentIndexY);
    path.push_back(currentPoint);
    findPath(targetCoordinate, enemySpeed, currentIndexX, currentIndexY, isOnXAxis);
}

//helper function to create new piont on the path for path2
void Map::getPath(double& targetCoordinate, double& currentIndexX, double& currentIndexY, bool v2, bool isOnXAxis){
    if(!v2){
        getPath(targetCoordinate, currentIndexX, currentIndexY, isOnXAxis);
        return;
    }
    QPoint* currentPoint = new QPoint();
    currentPoint->setX(currentIndexX);
    currentPoint->setY(currentIndexY);
    path2.push_back(currentPoint);
    findPath(targetCoordinate, enemySpeed, currentIndexX, currentIndexY, isOnXAxis);
}

//update indices according to targetCoordinate
void Map::findPath(double& targetCoordinate, double& enemySpeed, double& indexX, double& indexY, bool isOnXAxis){
    if(isOnXAxis){
        if(targetCoordinate > indexX){
            indexX+=enemySpeed;
        }
        else{
            indexX-=enemySpeed;
        }
    }
    else{
        if(targetCoordinate > indexY){
            indexY+=enemySpeed;
        }
        else{
            indexY-=enemySpeed;
        }
    }
}

void Map::setHealthLabelText(int num){

    lblHealth->setText("Health: " + (QString::number(num)));
}

void Map::setLevelLabelText(int num){
    lblLevel->setText("Level: " + (QString::number(num)));
}

void Map::setCoinsLabelText(int num){

    Coins = num;
    lblCoins->setText("Coin Balance: " + (QString::number(num)));


}

void Map::setEnemySpeed(double numPixelsPerMove){
    enemySpeed = numPixelsPerMove;
}

int Map::getcoinbalance()
{
    return Coins;
}

void Map::showShop()
{
    Shop *shop = new Shop(NULL,this);
    shop->show();
    connect(shop, &Shop::deploycannon, this, &Map :: deploythecannon);
    connect(shop, &Shop::deploytesla, this, &Map :: deploythetesla);
    connect(shop, &Shop::deployinferno, this, &Map :: deploytheinferno);
    connect(shop, &Shop::deployxbow, this, &Map :: deploythexbow);

}

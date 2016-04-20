#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "galaga.h"

extern Galaga * galaga;

Enemy::Enemy(QGraphicsItem*parent):QObject(), QGraphicsPixmapItem(parent)
{
    //set random position
    int randNum = rand() % 425;
    setPos(randNum,0);

    //making bullet that is rectangle
    setPixmap(QPixmap(":/images/enemy.png"));
    setTransformOriginPoint(35,19);
    setRotation(270);

    //connecting timer(signal) to slot
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    //every 50 ms the bullet will move
    timer->start(50);
}

void Enemy::move()
{
    //move enemy down
    setPos(x(),y()+5);
    if (pos().y() > 750){
        //decrease health
        galaga->health->decreaseHealth();

        scene()->removeItem(this);
        delete this;
    }
}

#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "galaga.h"
#include "typeinfo"

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
    if(galaga->score->getScore() < 20){
        setPos(x(),y()+5);
    }
    else
        setPos(x(),y()+10);
    if (pos().y() > 750){
        //decrease health
        galaga->health->decreaseHealth();

        scene()->removeItem(this);
        delete this;
    }
    //decreases health if enemy runs into player
    QList<QGraphicsItem*> colliding = collidingItems();
    for(int i = 0; i<colliding.size(); i++){
        if(typeid(*(colliding[i])) == typeid(player)){
            //decreases the health
            galaga->health->decreaseHealth();

            //remove enemy
            scene()->removeItem(this);
            //delete enemy
            delete this;
            return;
        }
    }

}

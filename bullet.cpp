#include "bullet.h"
#include "enemy.h"
#include "galaga.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>

//we can access global object Galaga
extern Galaga * galaga;

Bullet::Bullet(QGraphicsItem * parent):QObject(), QGraphicsPixmapItem(parent)
{
    //making bullet
    setPixmap(QPixmap(":/images/bullet1.png"));

    //connecting timer(signal) to slot
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    //every 50 ms the bullet will move
    timer->start(50);
}

void Bullet::move()
{
    //checking to see if it collides with enemy
    QList<QGraphicsItem*> colliding = collidingItems();
    for(int i = 0; i<colliding.size(); i++){
        if(typeid(*(colliding[i])) == typeid(Enemy)){
            //increases the score
            galaga->score->increaseScore();

            //remove both
            scene()->removeItem(colliding[i]);
            scene()->removeItem(this);
            //delete both
            delete colliding[i];
            delete this;
            return;
        }
    }

    //move bullet up
    setPos(x(),y()-10);
    if (pos().y() < 0){
        scene()->removeItem(this);
        delete this;
    }
}

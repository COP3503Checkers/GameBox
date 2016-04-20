#include "bullet2.h"
#include "enemy.h"
#include "enemy2.h"
#include "galaga.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>

//we can access global object Galaga
extern Galaga * galaga;

BulletTwo::BulletTwo(QGraphicsItem * parent):QObject(), QGraphicsPixmapItem(parent)
{
    //making bullet
    setPixmap(QPixmap(":/images/bullet2.png"));

    //connecting timer(signal) to slot
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    //every 50 ms the bullet will move
    timer->start(50);
}

void BulletTwo::move()
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
        if(typeid(*(colliding[i])) == typeid(EnemyTwo)){
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
    setPos(x(),y()-20);
    if (pos().y() < 0){
        scene()->removeItem(this);
        delete this;
    }
}

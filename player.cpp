#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "health.h"
#include <QKeyEvent>
#include <QGraphicsScene>

player::player(QGraphicsItem *parent):QGraphicsPixmapItem(parent){
    //set graphic
    setPixmap(QPixmap(":/images/player1.png"));
}

void player::keyPressEvent(QKeyEvent *event)
{
    //moves player to left or right depending on the key
    if (event->key() == Qt::Key_Left){
        if(pos().x() > 10)
            setPos(x()-10,y());
    }
    else if (event->key() == Qt::Key_Right){
        if(pos().x()+100 < 515)
            setPos(x()+10,y());
    }

    //bullet
    else if (event->key() == Qt::Key_Space){
        Bullet * b = new Bullet();
        b->setPos(x()+20,y());
        scene()->addItem(b);
    }
}

void player::spawn()
{
    //create enemy
    Enemy *enemy = new Enemy();
    scene()->addItem(enemy);
}

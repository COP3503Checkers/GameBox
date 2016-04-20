#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "galaga.h"
#include "score.h"
#include "health.h"
#include "bullet2.h"
#include "enemy2.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>

extern Galaga * galaga;

player::player(QGraphicsItem *parent):QGraphicsPixmapItem(parent){
    //set sound
    bSound = new QMediaPlayer();
    bSound->setMedia(QUrl("qrc:/sounds/laser.mp3"));

    //set graphic
    setPixmap(QPixmap(":/images/player1.png"));
}

void player::keyPressEvent(QKeyEvent *event)
{
    //moves player to left or right depending on the key
    if (event->key() == Qt::Key_Left){
        if(pos().x() > 10){
            if(galaga->score->getScore() < 20)
                setPos(x()-15,y());
            else
                setPos(x()-22,y());
        }
    }
    else if (event->key() == Qt::Key_Right){
        if(pos().x()+50 < 525){
            if(galaga->score->getScore() < 20)
                setPos(x()+15,y());
            else
                setPos(x()+22,y());
        }
    }

    //bullet
    else if (event->key() == Qt::Key_Space){
        Bullet * b = new Bullet();
        b->setPos(x()+20,y());
        scene()->addItem(b);

        //play bullet sound
        if(bSound->state() == QMediaPlayer::PlayingState){
            bSound->setPosition(0);
        }
        else if(bSound->state() == QMediaPlayer::StoppedState){
             bSound->play();
        }

        if(galaga->score->getScore()>15){
              BulletTwo *b2 = new BulletTwo();
              b2->setPos(x()+20,y());
              scene()->addItem(b2);
        }
    }
}

void player::spawn()
{
    //create enemy
    Enemy *enemy = new Enemy();
    scene()->addItem(enemy);

    if(galaga->score->getScore() > 10){
        EnemyTwo * enemyTwo = new EnemyTwo();
        scene()->addItem(enemyTwo);
    }

}

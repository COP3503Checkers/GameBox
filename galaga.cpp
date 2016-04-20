#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "enemy.h"
#include "galaga.h"
#include <QBrush>
#include <QImage>
#include "gameover.h"
#include <QDebug>

Galaga::Galaga(QWidget*parent){

    //creating a scene
    scene = new QGraphicsScene();

    setBackgroundBrush(QBrush(QImage(":/images/background.png")));

    //creating an item
    p = new player();
    //sets the player at the bottom middle of the screen
    p->setPos(250,650);

    //create score
    score = new Score();
    scene->addItem(score);

    //create health
    health = new Health();
    health->setPos(health->x(),health->y()+30);
    scene->addItem(health);

    //adding item to scene
    scene->addItem(p);


    //making the item focusable
    p->setFlag(QGraphicsItem::ItemIsFocusable);
    p->setFocus();

    //the view won't get bigger as something moves in it
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //adding scene to the view
    setScene(scene);

    //showing the view and setting the scene and view to a certain size
    setFixedSize(525,750);
    scene->setSceneRect(0,0,525,750);

    //spawn enemies every 2 seconds
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),p,SLOT(spawn()));
    timer->start(2000);

    show();
}

#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

//with QOBJECT bullet can handle signals and slots

class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(QGraphicsItem* parent = 0);
public slots: //member function can be connected to a signal if it is under slots
    void move();

};

#endif // ENEMY_H

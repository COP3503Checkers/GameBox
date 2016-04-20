#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

//with QOBJECT bullet can handle signals and slots

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(QGraphicsItem * parent = 0);
public slots: //member function can be connected to a signal if it is under slots
    void move();

};

#endif // BULLET_H

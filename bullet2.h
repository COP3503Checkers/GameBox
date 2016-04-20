#ifndef BULLET2_H
#define BULLET2_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

//with QOBJECT bullet can handle signals and slots

class BulletTwo: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    BulletTwo(QGraphicsItem * parent = 0);
public slots: //member function can be connected to a signal if it is under slots
    void move();

};

#endif // BULLET2_H

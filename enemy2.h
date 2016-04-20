#ifndef ENEMY2_H
#define ENEMY2_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

//with QOBJECT bullet can handle signals and slots

class EnemyTwo: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    EnemyTwo(QGraphicsItem* parent = 0);
public slots: //member function can be connected to a signal if it is under slots
    void move();

};

#endif // ENEMY2_H

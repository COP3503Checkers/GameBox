#ifndef GALAGA_H
#define GALAGA_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "player.h"
#include "score.h"
#include "health.h"

class Galaga: public QGraphicsView{
public:
    Galaga(QWidget * parent = 0);

    QGraphicsScene * scene;
    player * p;
    Score * score;
    Health * health;
};

#endif // GALAGA_H

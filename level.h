#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsTextItem>

class Level: public QGraphicsTextItem{
public:
    Level(QGraphicsItem * parent = 0);
    void increaseLevel();
    int getLevel();

private:
    int level;
};

#endif // LEVEL_H

#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class player: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    player(QGraphicsItem * parent = 0);
    void keyPressEvent(QKeyEvent * event);
public slots:
    void spawn();
};

#endif // PLAYER_H

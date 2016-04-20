#include "health.h"
#include "player.h"
#include "galaga.h"
#include <QFont>

extern Galaga * galaga;

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    //health is initially 3
    health = 3;

    //health text
    setPlainText(QString("Lives: ")+QString::number(health));

    //changing the text color
    setDefaultTextColor(Qt::red);

    //name of the font and size of font
    setFont(QFont("times",20));
}

void Health::decreaseHealth()
{
    health--;
    //updates number of lives
    if(health>=0)
        setPlainText(QString("Lives: ")+QString::number(health));
    if(health == 0){
        setPlainText(QString("GAME OVER!"));
        setFont(QFont("times",55));
     /*   QList<QGraphicsItem*> list = galaga->items();
        for(int i = 0; i<list.size();i++){
            QGraphicsItem *g = list[i];
            removeItem(g);
            delete g; */

    }
}

int Health::getHealth()
{
    return health;
}

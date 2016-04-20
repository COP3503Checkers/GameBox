#include "level.h"
#include <QFont>

Level::Level(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    //level is initially 1
    level = 1;

    //level text
    setPlainText(QString("Level: ")+QString::number(level));

    //changing the text color
    setDefaultTextColor(Qt::red);

    //name of the font and size of font
    setFont(QFont("times",20));
}

void Level::increaseLevel()
{
    level++;
    //updates level
    setPlainText(QString("Level: ")+QString::number(level));

}

int Level::getLevel()
{
    return level;
}

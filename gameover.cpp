#include "gameover.h"
#include <QFont>
#include "score.h"

GameOver::GameOver(QGraphicsItem *parent): QGraphicsTextItem(parent)
{

    setPlainText(QString("Game Over"));
    //score text
    setPlainText(QString("Score: ")+QString::number(score));

    //changing the text color
    setDefaultTextColor(Qt::red);

    //name of the font and size of font
    setFont(QFont("times",100));
}

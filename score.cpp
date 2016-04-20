#include "score.h"
#include "level.h"
#include "galaga.h"
#include <QFont>

extern Galaga * galaga;

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    //score is initially 0
    score = 0;

    //score text
    setPlainText(QString("Score: ")+QString::number(score));

    //changing the text color
    setDefaultTextColor(Qt::red);

    //name of the font and size of font
    setFont(QFont("times",20));

}

void Score::increaseScore()
{
    score++;
    //updates score
    setPlainText(QString("Score: ")+QString::number(score));

    if(score==10)
        galaga->level->increaseLevel();
    if(score==20)
        galaga->level->increaseLevel();

}

int Score::getScore()
{
    return score;
}

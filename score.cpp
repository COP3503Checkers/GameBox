#include "score.h"
#include <QFont>

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

}

int Score::getScore()
{
    return score;
}

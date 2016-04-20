#include <QApplication>
#include "galaga.h"

Galaga * galaga;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    galaga = new Galaga();
    galaga->show();

    return a.exec();
}

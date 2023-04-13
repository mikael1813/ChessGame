#include <QtCore/QCoreApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    Game g;
    tuple<unsigned short int, unsigned short int> t = g.get_actual_postion("x3");
    QCoreApplication a(argc, argv);

    return a.exec();
}

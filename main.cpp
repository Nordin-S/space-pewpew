#include "headers/game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    space_pewpew::Game gameScene;
    return a.exec();
}

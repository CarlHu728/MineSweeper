#include "mainwindow.h"
#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Game myGame(LEVEL::CUSTOM, 10, 10, 1);
    myGame.Start();
    myGame.Print();
    myGame.Click(3, 3);
    myGame.Print();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

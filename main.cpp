#include "game.h"
#include "mainmenu.h"

#include <QApplication>

Game *game;
MainMenu *mainmenu;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    //mainmenu = new MainMenu();
    //mainmenu->show();

    return a.exec();
}


#include "game.h"
#include "mainmenu.h"

#include <QApplication>

Game *game;
MainMenu *mainmenu;

/*
 * Remaining Issues:
 * Plane accelerates and decelerates slower - Limit is 21/9/2015
 * When landing on runway, plane is on white lines, not on grey border - Limit is 21/9/2015
 * RC increases and decreases more radically with angle change - Limit is 21/9/2015
 * Improve Background and Runway to make them match more and look better together
 * Add land airport (after 1.0 released)
 * Make Airplane (Cessna 172) Pixmap - Limit is 21/9/2015
 * Improve clouds
 * Implement brakes + spoilers - Limit is 21/9/2015
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    //mainmenu = new MainMenu();
    //mainmenu->show();

    return a.exec();
}


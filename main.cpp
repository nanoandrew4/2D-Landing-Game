#include "game.h"

#include <QApplication>

Game *game;

/*
 * Remaining Issues:
 * Plane accelerates and decelerates slower - Limit is 21/9/2015 - Done 22:20 20/9/2015
 * Plane acceleration and deceleration is in smaller steps
 * When landing on runway, plane is on white lines, not on grey border - Limit is 21/9/2015 - Done 23:57 20/9/2015
 * RC increases and decreases more radically with angle change - Limit is 21/9/2015 - Done 13:01 20/9/2015
 * Improve Background and Runway to make them match more and look better together - Done 13:01 20/9/2015
 * Add land airport (after 1.0 released)
 * Make Airplane (Cessna 172) Pixmap - Limit is 21/9/2015
 * Improve clouds
 * Implement brakes + spoilers - Limit is 21/9/2015
 * Make turning aircraft and accelerating/decelerating smoother - Limit is 21/9/2015 - Done 22:20 20/9/2015
 * Fix drag - Limit is 21/9/2015
 * Fix altitude display, so that it displays right - Limit is 21/9/2015 - Done 16:55 20/9/2015
 * Implement Wind and MicroBursts
 */

/*
 * Changes:
 * Added pitch to be displayed
 * Added slower acceleration and deceleration
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();

    return a.exec();
}


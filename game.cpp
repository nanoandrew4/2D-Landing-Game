#include "game.h"
#include "plane.h"
#include "mainmenu.h"


int screenWidth = 1280;
int screenHeight = 720;
int sceneWidth = 5000;

Game::Game()
{

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,sceneWidth, screenHeight);

    setFixedSize(screenWidth, screenHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);

    landingStrip = new QGraphicsRectItem();
    landingStrip->setRect(0,0,screenWidth /6,screenHeight /6);
    landingStrip->setPos(sceneWidth - 500, screenHeight - screenHeight /6);
    scene->addItem(landingStrip);

    plane = new Plane();
    scene->addItem(plane);

    engine = new Engine();

    show();

}

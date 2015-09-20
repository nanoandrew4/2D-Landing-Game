#include "game.h"
#include "plane.h"
#include "mainmenu.h"

#include <QGraphicsPixmapItem>


int screenWidth = 1280;
int screenHeight = 720;
int sceneWidth = 5000;

void Game::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(0,0, sceneWidth, screenHeight, QPixmap(":/Graphics/Graphics/Background.png"));
}

Game::Game()
{

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,sceneWidth, screenHeight);

    setFixedSize(screenWidth, screenHeight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);

    landingStrip = new QGraphicsPixmapItem();
    landingStrip->setPixmap(QPixmap(":/Graphics/Graphics/Runway.png"));
    landingStrip->setPos(sceneWidth - 700, screenHeight -315 );
    scene->addItem(landingStrip);

    plane = new Plane();
    scene->addItem(plane);

    engine = new Engine();

    show();

}


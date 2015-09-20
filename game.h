#ifndef GAME
#define GAME

#include "plane.h"
#include "engine.h"
#include "mainmenu.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

class Game : public QGraphicsView{
public:
    Game();
    QGraphicsScene *scene;
    QGraphicsRectItem *landingStrip;
    Plane *plane;
    Engine *engine;
    MainMenu *mainmenu;

};

#endif // GAME


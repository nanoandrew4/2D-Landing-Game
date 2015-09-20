#include "mainmenu.h"
#include "game.h"

extern int screenWidth;
extern int screenHeight;

#include <QPushButton>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent){

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,screenWidth, screenHeight);

    setFixedSize(screenWidth, screenHeight);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene);

    playButton = new QPushButton("Play", this);
    playButton->setGeometry(screenWidth /2, 100, 100,50);

    exitButton = new QPushButton("Exit", this);
    playButton->setGeometry(screenWidth /2, 200, 100, 50);

    connect(playButton, SIGNAL(released()), this, SLOT(play()));
    connect(exitButton, SIGNAL(released()), this, SLOT(exit()));

    show();
}

void MainMenu::play()
{
    delete playButton;
    delete exitButton;
    //delete controlsButton;
    Game *game = new Game();
    game->show();
}

void MainMenu::exit()
{
    delete playButton;
    delete exitButton;
    delete controlsButton;
    exit();
}

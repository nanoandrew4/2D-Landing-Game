/*
 * This class controls the whole game, the scene and all other classes found in the game. It also is in charge of displaying data from
 * the other classes on the screen.
 */

#include "game.h"
#include "plane.h"
#include "engine.h"

#include <QGraphicsPixmapItem>
#include <QFont>
#include <QDebug>
#include <cstdlib>

int screenWidth = 1280;
int screenHeight = 720;
int sceneWidth = 5000;
double viewX = 0; // will calculate distance to view border

extern double airspeed;
extern int planeAngle;
extern double RC;
extern double altitude;
extern int flapAngle;
extern int spoiler;
extern int brakes;
extern bool crash;
extern bool succesfulLanding;
extern Game *game;

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

    engine = new Engine();

    plane = new Plane();
    scene->addItem(plane);


    //adding all relevant data to screen

    airspeedText = new QGraphicsTextItem();
    airspeedText->setFont(QFont("times", 12));
    scene->addItem(airspeedText);

    planeAngleText = new QGraphicsTextItem();
    planeAngleText->setFont(QFont("times", 12));
    scene->addItem(planeAngleText);

    RCtext = new QGraphicsTextItem();
    RCtext->setFont(QFont("times", 12));
    scene->addItem(RCtext);

    altitudeText = new QGraphicsTextItem();
    altitudeText->setFont(QFont("times", 12));
    scene->addItem(altitudeText);

    flapAngleText = new QGraphicsTextItem();
    flapAngleText->setFont(QFont("times", 12));
    scene->addItem(flapAngleText);

    spoilerPosText = new QGraphicsTextItem();
    spoilerPosText->setFont(QFont("times", 12));
    scene->addItem(spoilerPosText);

    brakesText = new QGraphicsTextItem();
    brakesText->setFont(QFont("times", 12));
    scene->addItem(brakesText);

    youLostText = new QGraphicsTextItem();
    youLostText->setFont(QFont("times", 40));

    youWonText = new QGraphicsTextItem();
    youWonText->setFont(QFont("times", 40));

    updateTextTimer = new QTimer();
    connect(updateTextTimer, SIGNAL(timeout()), this, SLOT(updateText()));
    updateTextTimer->start(1000/30);

    replayButton = new QPushButton("Replay", this);
    replayButton->setGeometry(QRect(QPoint(pos().x() + 450, 400), QSize(50,25)));
    connect(replayButton, SIGNAL(released()), this, SLOT(replay()));
    replayButton->hide();

    exitButton = new QPushButton("Exit", this);
    exitButton->setGeometry(QRect(QPoint(pos().x() + 700, 400), QSize(50,25)));
    connect(exitButton, SIGNAL(released()), this, SLOT(exit()));
    exitButton->hide();

    show();

}

void Game::updateText()
{
    viewX = plane->pos().x() - 600;
    airspeedText->setPlainText(QString("Airspeed: ") + QString::number(airspeed));
    if(viewX <= 0){airspeedText->setPos(0,2);}
    else if(viewX > 0 && viewX < 3725){airspeedText->setPos(viewX, 2);}
    else if(viewX >= 3720){airspeedText->setPos(3725, 2);}

    planeAngleText->setPlainText(QString("Pitch: ") + QString::number(-planeAngle) + QString("º"));
    if(viewX <= 0){planeAngleText->setPos(0, 18);}
    else if(viewX > 0 && viewX < 3725){planeAngleText->setPos(viewX, 18);}
    else if(viewX >= 3720){planeAngleText->setPos(3725, 18);}

    RCtext->setPlainText((QString("Rate Of Climb: ") + QString::number(-RC)));
    if(viewX <= 0){RCtext->setPos(0,34);}
    else if(viewX > 0 && viewX < 3725){RCtext->setPos(viewX, 34);}
    else if(viewX >= 3720){RCtext->setPos(3725, 34);}

    altitudeText->setPlainText((QString("Altitude: ") + QString::number(screenHeight * 27.7 - altitude *27.7 -3000)));
    if(viewX <= 0){altitudeText->setPos(0,50);}
    else if(viewX > 0 && viewX < 3725){altitudeText->setPos(viewX, 50);}
    else if(viewX >= 3720){altitudeText->setPos(3725, 50);}

    flapAngleText->setPlainText((QString("Flap Angle: ") + QString::number(flapAngle)));
    if(viewX <= 0){flapAngleText->setPos(0,66);}
    else if(viewX > 0 && viewX < 3725){flapAngleText->setPos(viewX, 66);}
    else if(viewX >= 3720){flapAngleText->setPos(3725, 66);}

    if(spoiler == 0){spoilerPosText->setPlainText("Spoilers: Unarmed");}
    else if(spoiler == 1){spoilerPosText->setPlainText("Spoilers: Flight");}
    else if(spoiler == 2){spoilerPosText->setPlainText("Spoilers: Armed");}
    if(viewX <= 0){spoilerPosText->setPos(0,82);}
    else if(viewX > 0 && viewX < 3725){spoilerPosText->setPos(viewX, 82);}
    else if(viewX >= 3720){spoilerPosText->setPos(3725, 82);}

    if(brakes == 0){brakesText->setPlainText("Brakes: Off");}
    if(brakes == 1){brakesText->setPlainText("Brakes: On");}
    if(viewX <= 0){brakesText->setPos(0,98);}
    else if(viewX > 0 && viewX < 3725){brakesText->setPos(viewX, 98);}
    else if(viewX >= 3720){brakesText->setPos(3725, 98);}

    if(succesfulLanding == true || crash == true){
        if(succesfulLanding == true){
        youWonText->setPlainText("You landed succesfuly!");
        youWonText->setPos(4100, 300);
        scene->addItem(youWonText);
        }
        if(crash == true){
            scene->removeItem(plane);
            youLostText->setPlainText("You crashed the airplane");
            if(viewX <= 0){youLostText->setPos(350, 300);}
            if(viewX > 0 && viewX < 3725){youLostText->setPos(viewX + 350, 300);}
            if(viewX >= 3720){youLostText->setPos(4100, 300);}
            scene->addItem(youLostText);
        }

        updateTextTimer->stop();

        scene->removeItem(airspeedText);
        scene->removeItem(RCtext);
        scene->removeItem(planeAngleText);
        scene->removeItem(altitudeText);
        scene->removeItem(flapAngleText);
        scene->removeItem(spoilerPosText);
        scene->removeItem(brakesText);

        delete airspeedText;
        delete RCtext;
        delete planeAngleText;
        delete altitudeText;
        delete flapAngleText;
        delete spoilerPosText;
        delete brakesText;

        replayButton->show();
        exitButton->show();

        return;
    }
}

void Game::replay()
{
    game->close();

    delete plane;
    delete engine;
    scene->removeItem(landingStrip);
    delete landingStrip;
    delete exitButton;
    delete replayButton;
    scene->removeItem(youLostText);
    delete youLostText;
    delete scene;

    crash = false;

    game = new Game();
    game->show();
}

void Game::exit()
{
    delete plane;
    scene->removeItem(landingStrip);
    delete landingStrip;
    delete engine;
    delete exitButton;
    delete replayButton;
    scene->removeItem(youLostText);
    delete youLostText;
    delete scene;
    exit();
}

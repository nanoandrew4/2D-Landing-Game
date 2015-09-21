/*
 * This class controls the whole game, the scene and all other classes found in the game. It also is in charge of displaying data from
 * the other classes on the screen.
 */

#include "game.h"
#include "plane.h"
#include "engine.h"

#include <QGraphicsPixmapItem>
#include <QFont>

int screenWidth = 1280;
int screenHeight = 720;
int sceneWidth = 5000;

extern double airspeed;
extern int planeAngle;
extern double RC;
extern double altitude;
extern int flapAngle;
extern int spoiler;
extern int brakes;
extern bool crash;

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

    updateTextTimer = new QTimer();
    connect(updateTextTimer, SIGNAL(timeout()), this, SLOT(updateText()));
    updateTextTimer->start(1000/30);

    show();

}

void Game::updateText()
{
    airspeedText->setPlainText(QString("Airspeed: ") + QString::number(airspeed));
    airspeedText->setPos(plane->pos().x() -600, 2);

    planeAngleText->setPlainText(QString("Pitch: ") + QString::number(-planeAngle) + QString("º"));
    planeAngleText->setPos(plane->pos().x() -600, 18);

    RCtext->setPlainText((QString("Rate Of Climb: ") + QString::number(-RC)));
    RCtext->setPos(plane->pos().x() -600, 34);

    altitudeText->setPlainText((QString("Altitude: ") + QString::number(screenHeight * 27.7 - altitude *27.7)));
    altitudeText->setPos(plane->pos().x() - 600, 50);

    flapAngleText->setPlainText((QString("Flap Angle: ") + QString::number(flapAngle)));
    flapAngleText->setPos(plane->pos().x() -600, 66);

    if(spoiler == 0){spoilerPosText->setPlainText("Spoilers: Unarmed");}
    if(spoiler == 1){spoilerPosText->setPlainText("Spoilers: Flight");}
    if(spoiler == 2){spoilerPosText->setPlainText("Spoilers: Armed");}
    spoilerPosText->setPos(plane->pos().x() -600, 82);

    if(brakes == 0){brakesText->setPlainText("Brakes: Off");}
    if(brakes == 1){brakesText->setPlainText("Brakes: On");}
    brakesText->setPos(plane->pos().x() -600, 98);

    if(crash == true){
        youLostText->setPlainText("You crashed the airplane");
        youLostText->setPos(plane->pos().x() -400, 340);
        scene->addItem(youLostText);
        updateTextTimer->stop();

        replay = new QPushButton("Replay", this);
        replay->setGeometry(QRect(QPoint(4500, 400), QSize(100,50)));
    }
    show();

}

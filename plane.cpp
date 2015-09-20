#include "plane.h"
#include "game.h"

#include <QKeyEvent>
#include <QList>
#include <QDebug>

extern int screenWidth;
extern int screenHeight;
extern int sceneWidth;
extern int planeAngle;
extern int flapAngle;
extern double speed;
extern double airspeed;
extern double RC;

Plane::Plane()
{
    setRect(0,0,50,30);
    setPos(4000, screenHeight /3);
    setRotation(planeAngle);
    setFlags(QGraphicsItem::ItemIsFocusable);
    setFocus();

    moveTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(movePlane()));
    moveTimer->start(1000/33);

    thrustTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(planeThrust()));
    thrustTimer->start(100);
}

double altitude = screenHeight /3;
double planeMinSpeed = 0.0;
double planeMaxSpeed = 1.1;
int flapPressCount = 0;
int spoilerPressCount = 0;
int brakesPressCount = 0;
int thrust = 50;

void Plane::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up){
        if(thrust < 100){
        thrust++;
        }
    }
    if(event->key() == Qt::Key_Down){
        if(thrust > 0){
        thrust--;
        }
    }
    if(event->key() == Qt::Key_Right){
        if(planeAngle < 90){
            planeAngle++;
        }
    }
    if(event->key() == Qt::Key_Left){
        if(planeAngle > -90){
            planeAngle--;
        }
    }
    if(event->key() == Qt::Key_F){
        if(flapAngle < 40){
            flapAngle++;
        }
        /*
        flapPressCount++;
        switch (flapPressCount) {
        case 1:
        {
            flapAngle = 2;
            break;
        }
        case 2:
        {
            flapAngle = 7;
            break;
        }
        case 3:
        {
            flapAngle = 17;
            break;
        }

        default:
            flapPressCount = 0;
            break;
        }
        */
    }
    if(event->key() == Qt::Key_G){
        if(flapAngle > 0){
            flapAngle--;
        }
    }
    if(event->key() == Qt::Key_Escape){
        altitude = pos().y();
        setPos(x(), y());
        qDebug()<< "escape pressed";
    }
}

void Plane::planeThrust()
{
    speed = thrust * 2.35;
}

void Plane::movePlane()
{
    altitude += RC;

    setRotation(planeAngle);

    extern Game *game;
    game->centerOn(this);

    if(pos().y() < 0 || pos().y() > screenHeight || pos().x() > sceneWidth){
        qDebug()<<"plane deleted";
        delete this;
        exit(EXIT_SUCCESS);
        //return;
    }
    QList< QGraphicsItem *> collisionCheck = collidingItems();

    if(collisionCheck.size() == 1){
        setPos(x() + airspeed *1000/36000, y()); //make altitude equal to y better, that way one bug is avoided where after contact is over or if you overshoot the plane drops to where it was supposed to be
        return;
    }
    setPos(x() + airspeed *1000/36000, altitude); // 36000 to make it fit to the scene, should be 3600 for m/s

    //qDebug() << pos().x();
    //qDebug()<<altitude;
    //qDebug()<<airspeed;
    //qDebug()<<planeAngle;
    //qDebug()<<planeMaxSpeed;
    //qDebug()<<flapAngle;

}



void Plane::brakesActivated()
{

}

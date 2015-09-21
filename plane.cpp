/*
 * This class is in charge of the plane object, of drawing it, recieving input from keys to make plane function, as well as making any
 * necessary changes to the different variables that control its movement through the scene. Also controls collisions with other objects
 *  (such as the runway) and deletes the plane and exits the program if the plane goes off the scene.
 */

#include "plane.h"
#include "game.h" //to use centerOn function

#include <QKeyEvent>
#include <QList>
#include <QDebug>

extern int screenWidth;
extern int screenHeight;
extern int sceneWidth;
extern int planeAngle;
extern int flapAngle;
extern int spoiler;
extern double speed;
extern double airspeed;
extern double RC;

double altitude = screenHeight /3;
int brakes = 0;
int thrust = 50;

Plane::Plane()
{
    setRect(0,0,85,50);
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
    }
    if(event->key() == Qt::Key_G){
        if(flapAngle > 0){
            flapAngle--;
        }
    }
    if(event->key() == Qt::Key_S){
        if(spoiler == 2){
            spoiler = -1; //so that when spoiler is increased, equals 0 and not 1
        }
        if(spoiler < 2){
            spoiler++;
        }

    }
    if(event->key() == Qt::Key_B){
        if(brakes == 1){brakes = -1;}
        brakes++;
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

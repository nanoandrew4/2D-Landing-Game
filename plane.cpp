/*
 * This class is in charge of the plane object, of drawing it, recieving input from keys to make plane function, as well as making any
 * necessary changes to the different variables that control its movement through the scene. Also controls collisions with other objects
 *  (such as the runway) and deletes the plane and exits the program if the plane goes off the scene.
 */

#include "plane.h"
#include "game.h" //to use centerOn function

#include <QKeyEvent>
#include <QFont>
#include <cmath>

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
bool brakes = false;
int thrust = 50;
bool crash = false;
bool succesfulLanding = false;
bool brakesOk = false;
int key[4]; //for ability to recieve 2 keys at once instead of 1, also fixes fluidity when change in planeAngle
int limit = 90; //variable so that when plane lands, it can't go into the ground

Plane::Plane()
{
    setPixmap(QPixmap(":/Graphics/Graphics/Plane.png"));
    setPos(75, screenHeight /3);
    setRotation(planeAngle);
    setFlags(QGraphicsItem::ItemIsFocusable);
    setFocus();
    speed = 117.5; //so that the plane starts at reasonable speed

    moveTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(movePlane()));
    moveTimer->start(1000/33);

    thrustTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(planeThrust()));
    thrustTimer->start(250);
}

void Plane::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
        {
        case Qt::Key_Up:
            key[0] = 1;
            break;
        case Qt::Key_Down:
            key[1] = 1;
            break;
        case Qt::Key_Left:
            key[2] = 1;
            break;
        case Qt::Key_Right:
            key[3] = 1;
            break;
        case Qt::Key_F:
            if(flapAngle < 40){flapAngle++;}else{flapAngle = 0;}
            break;
        case Qt::Key_G:
            if(flapAngle > 0){flapAngle--;}
            break;
        case Qt::Key_S:
            if(spoiler < 2){spoiler++;}else{spoiler = 0;}
            break;
        case Qt::Key_B:
            if(brakesOk == true){brakes = true;}
    }
}

void Plane::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        key[0] = 0;
        break;
    case Qt::Key_Down:
        key[1] = 0;
        break;
    case Qt::Key_Left:
        key[2] = 0;
        break;
    case Qt::Key_Right:
        key[3] = 0;
        break;
    }
}

void Plane::planeThrust()
{
    if(speed <= thrust * 2.35){speed += 1.175;}
    if(speed > thrust * 2.35){speed -= 1.175;}

}

void Plane::movePlane()
{

    if(key[0] == 1 && key[2] == 1){if(thrust < 100){thrust++;} if(planeAngle > -90){planeAngle--;}} //Up arrow + left arrow
    else if(key[0] == 1 && key[3] == 1){if(thrust < 100){thrust++;} if(planeAngle < limit)planeAngle++;} //Up arrow + right arrow
    else if(key[1] == 1 && key[2] == 1){if(thrust > 0){thrust--;} if(planeAngle > -90)planeAngle--;} //Up arrow + left arrow
    else if(key[1] == 1 && key[3] == 1){if(thrust > 0){thrust--;} if(planeAngle < limit)planeAngle++;} //Up arrow + right arrow
    else if(key[0] == 1 && thrust < 100){thrust++;}
    else if(key[1] == 1 && thrust > 0){thrust--;}
    else if(key[2] == 1 && planeAngle > -90){planeAngle--;}
    else if(key[3] == 1 && planeAngle < limit){planeAngle++;}

    setRotation(planeAngle);

    if((-RC < -2.5 && pos().x() > 4400 && pos().y() > screenHeight - 313) || (pos().y() > 600) || (pos().x() > 4265 && pos().y() > screenHeight - 311.5)){
        crash = true;
        altitude = screenHeight /3;
        RC = 0;
        thrust = 50;
        speed = 117.5;
        flapAngle = 0;
        planeAngle = -10;
        moveTimer->stop();
        thrustTimer->stop();
        return;
    }

    if(pos().y() < 0 || pos().x() > sceneWidth){
        delete this;
        exit(EXIT_SUCCESS);
    }

    if(brakes == true && speed > 0){
        speed -= sin(speed)*5;
        thrust = 0;
    }

    if(pos().x() > 4400 && pos().y() > screenHeight - 313 && pos().y() < screenHeight -311.5){
        brakesOk = true;
        limit = 0;
        if(speed <= 5){
            succesfulLanding = true;
            return;
        }
        setPos(x() + airspeed *1000/36000, y());
        altitude = pos().y();
        return;
    }

    extern Game *game;
    game->centerOn(this);

    altitude += RC;
    setPos(x() + airspeed *1000/36000, altitude); // 36000 to make it fit to the scene, should be 3600 for m/s
}

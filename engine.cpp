#include "engine.h"
#include "plane.h"

#include <QDebug>
#include <cmath>

extern Plane *plane;

extern int screenHeight;
extern double altitude;
extern double planeMaxSpeed;
extern double planeMinSpeed;

double density = 0;
double pressure = 0;
double temp = 0;
double R = 287.05;
double Cl = 0.8;
double speed = 0;
double airspeed = 0.0;
double planeAngle = 10;
int weight = 800;
double gravForce = weight * 9.81;
double drag = 0;
double Sref = 16.2;
double lift = 0;
double psf2Pa = 47.88;
int flapAngle = 0;
int spoiler = 0;
double RC = 0;
double pi = 3.14159265;
double radianConvert = pi /180;

Engine::Engine()
{
    /*
    gravTimer = new QTimer();
    connect(gravTimer, SIGNAL(timeout()), this, SLOT(gravity()));
    gravTimer->start(100);

    windTimer = new QTimer();
    connect(windTimer, SIGNAL(timeout()), this, SLOT(wind()));
    windTimer->start(1000/33);

    microTimer = new QTimer();
    connect(microTimer, SIGNAL(timeout()), this, SLOT(microBursts()));
    microTimer->start(1000/33);
    //qDebug()<<"ended engine start";
    */

    planeMechTimer = new QTimer();
    connect(planeMechTimer, SIGNAL(timeout()), this, SLOT(planeMechanics()));
    planeMechTimer->start(1000/30);

}

void Engine::planeMechanics()
{
    //drag seems not to be working, check once everything is implemented

        temp = 288.15 - (0.00396 * (3.28/2)) * (screenHeight - altitude *27.7); // temperature in kelvin minus altitude times constant decrease per 2 feet divided by 2 in temperature (from data in performance check). Times 27.7 to make it scaled so that altitudes work compared to actual data
        pressure = (2116.2 * pow(0.92532477, (screenHeight - altitude *27.7) /1000)) *psf2Pa; // multiply pressure at 0 feet by the ratio of decrease of pressure every foot. No need for metric conversion since psf is imperial. Taken from pattern in data on flight performance analysis
        density = pressure / (temp * R);

        drag = abs(cos((speed /1.6) * radianConvert)); //needs fixing so that is incremental at decent rate, fixed, just using absolute value
        airspeed = speed - drag; //need to be implemented in the game so that it increases and decreases at a certain rate, done

        Cl = speed /145;
        lift = density * (0.5*pow(airspeed,2)) * Sref * Cl * cos(flapAngle * radianConvert); //use cosine since at 90mph is when best RC happens, done
        //RC change with speed needs to be fixed, very extreme now, needs to be more modest
        RC = ((((lift / gravForce) /50) * (sin((airspeed / 20) *radianConvert)) / cos(flapAngle * radianConvert)) - gravForce /55000) / (1/planeAngle);

        // speed should increase way more when on a negative pitch, should make changes more extreme to speed, done
        // NEW - vertical displacement is barely affected, needs to be fixed by incrementing values or reducing airspeed in game
        if(planeAngle > 0){airspeed *= cos(planeAngle*radianConvert); RC /= cos(planeAngle*radianConvert);} //increase lift and decrease speed at constant ratio, will want to do by increments in the game
        if(planeAngle < 0){airspeed /= cos(planeAngle*radianConvert); RC *= sin(planeAngle*radianConvert)*RC;} //increase speed and decrease lift, RC, will want to do by increments in the game

        if(spoiler == 1){drag /= (cos(airspeed*(89.0/235.0) *radianConvert) *9); RC -= cos(speed*(89.0/speed) *radianConvert);} //degrees and max speed (235) must be decimals or won't work
        if(spoiler == 2){drag /= (cos(airspeed*(89.0/235.0) *radianConvert) *2); RC -= (cos(speed*(89.0/speed) *radianConvert) *140);}

        //qDebug()<<drag;
        qDebug()<<RC;
}

int windRand = 0;

//use global variable as angle-speed relation

void Engine::wind()
{
    windRand = rand() %3;
    switch(windRand){
        case 0: //right
            planeMaxSpeed+=0.2;
            planeMinSpeed+=0.2;
        break;
        case 1: //left
            planeMaxSpeed-=0.2;
            //planeMinSpeed-=0.2;
        break;
        case 2: //down
        break;
        case 3: //up
        break;
    }
}

void Engine::microBursts()
{

}

#ifndef GAME
#define GAME

#include "plane.h"
#include "engine.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPushButton>

class Game : public QGraphicsView{
    Q_OBJECT
public:
    Game();
    QGraphicsScene *scene;

private:
    QGraphicsPixmapItem *landingStrip;
    Plane *plane;
    Engine *engine;

    QPushButton *playButton;
    QPushButton *controlsButton;
    QGraphicsTextItem *welcomeText;
    QGraphicsPixmapItem *backgroundImage;

    QGraphicsTextItem *airspeedText;
    QGraphicsTextItem *RCtext;
    QGraphicsTextItem *altitudeText;
    QGraphicsTextItem *flapAngleText;
    QGraphicsTextItem *spoilerPosText;
    QGraphicsTextItem *brakesText;
    QGraphicsTextItem *planeAngleText;
    QGraphicsTextItem *youLostText;
    QGraphicsTextItem *youWonText;

    QTimer *updateTextTimer;
    QTimer *timer;

    QPushButton *replayButton;
    QPushButton *exitButton;
private slots:
    void updateText();
    void play();
    void controls();
    void replay();
    void mainMenu();
    void exit();
};

#endif // GAME


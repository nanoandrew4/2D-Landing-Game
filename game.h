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
    Plane *plane;
    Engine *engine;
private:
    void drawBackground(QPainter *painter, const QRectF &rect);
    QGraphicsPixmapItem *landingStrip;
    QGraphicsTextItem *airspeedText;
    QGraphicsTextItem *RCtext;
    QGraphicsTextItem *altitudeText;
    QGraphicsTextItem *flapAngleText;
    QGraphicsTextItem *spoilerPosText;
    QGraphicsTextItem *brakesText;
    QGraphicsTextItem *planeAngleText;
    QGraphicsTextItem *youLostText;
    QTimer *updateTextTimer;
    QPushButton *replayButton;
    QPushButton *exitButton;
private slots:
    void updateText();
    void replay();
    void exit();

};

#endif // GAME


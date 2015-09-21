#ifndef GAME
#define GAME

#include "plane.h"
#include "engine.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

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
    QTimer *updateTextTimer;
private slots:
    void updateText();

};

#endif // GAME


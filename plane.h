#ifndef PLANE
#define PLANE

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class Plane : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Plane();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private slots:
    void movePlane();
    void planeThrust();
private:
    QTimer *moveTimer;
    QTimer *thrustTimer;
    QGraphicsTextItem *youLostText;
};

#endif // PLANE


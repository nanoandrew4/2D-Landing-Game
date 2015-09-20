#ifndef PLANE
#define PLANE

#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>

class Plane : public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Plane();
    void keyPressEvent(QKeyEvent *event);
private slots:
    void movePlane();
    void brakesActivated();
private:
    QTimer *moveTimer;
};

#endif // PLANE


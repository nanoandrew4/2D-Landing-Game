#ifndef ENGINE
#define ENGINE

#include <QTimer>
#include <QObject>

class Engine : public QObject{
    Q_OBJECT
public:
    Engine();
public slots:
    void planeMechanics();
    //void gravity();
    void wind();
    void microBursts();
private:
    QTimer *planeMechTimer;
    //QTimer *gravTimer;
    QTimer *windTimer;
    QTimer *microTimer;
};

#endif // ENGINE


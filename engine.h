#ifndef ENGINE
#define ENGINE

#include <QTimer>
#include <QObject>

class Engine : public QObject{
    Q_OBJECT
public:
    Engine();
private slots:
    void planeMechanics();
    void wind();
    void microBursts();
private:
    QTimer *planeMechTimer;
    QTimer *windTimer;
    QTimer *microTimer;
};

#endif // ENGINE


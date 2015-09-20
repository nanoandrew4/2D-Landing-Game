#ifndef MAINMENU
#define MAINMENU

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsView>


class MainMenu : public QWidget{
Q_OBJECT
public:
    MainMenu(QWidget *parent = 0);
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *playButton;
    QPushButton *exitButton;
    QPushButton *controlsButton;
private:
public slots:
    void play();
    void exit();

};

#endif // MAINMENU


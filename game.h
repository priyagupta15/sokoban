#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QEvent>
#include <QObject>

#include "map.h"

class Game : public QGraphicsView
{
    Q_OBJECT

public slots:
     void nextLevel();

public:
    Game();
    ~Game();
    void restartLevel();

    Player *player;
    QGraphicsScene *scene;
    Map *map;
    int level;
};

#endif // GAME_H

#ifndef MAP_H
#define MAP_H

#include <QGraphicsPixmapItem>
#include <QFile>
#include <QGraphicsScene>
#include <QVector>
#include <QTextStream>
#include <QGraphicsSimpleTextItem>
#include "player.h"
#include "cell.h"
#include "stone.h"

enum mapConsts
{
    MAP_FLOOR = 0,
    MAP_WALL,
    MAP_TARGET
};

class Map
{
private:
    Cell *map[16][16];
    QGraphicsScene *scene;
    QString textures[3] =
    {
        ":/images/gfx_sokoban/kafelka.png",
        ":/images/gfx_sokoban/murek.png",
        ":/images/gfx_sokoban/kafelka2.png"
    };
public:
    QVector<Stone *> stones;
    Map(int level, QGraphicsScene *sc);
    ~Map();
    Cell * getCellByPos(int x, int y);
    Stone * getStoneByPos(int x, int y);
    bool isStoneAtPos(int x, int y) const;
    bool isLevelFinished() const;
    void clear();
};



#endif // MAP_H

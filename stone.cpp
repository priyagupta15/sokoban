#include "stone.h"
#include <QTimer>
#include <QPropertyAnimation>
#include "game.h"


extern Game * game;


Stone::Stone(int x, int y):
    QObject(),
    QGraphicsPixmapItem()
{
        setPos(x, y);
        setPixmap(QPixmap(":/images/gfx_sokoban/kamien1.png"));
        setZValue(5);
        good = false;
}

void Stone::setGoodAndCheck()
{
    this->setGood();
    if(game->map->isLevelFinished())
    {
        QTimer::singleShot(800, game, &Game::nextLevel); //no idea why not slot
    }
}

void Stone::setGood()
{
    good = true;
    setPixmap(QPixmap(":/images/gfx_sokoban/kamien_hi1.png"));
}

void Stone::unSetGood()
{
    if(!good) return;

    good = false;
    setPixmap(QPixmap(":/images/gfx_sokoban/kamien1.png"));
}

QPoint Stone::getPosition() const
{
    return QPoint(x(), y());
}

void Stone::setPosition(QPoint p)
{
    setPos(p);
}

void Stone::animateStone(int d_x, int d_y, int typeMap)
{
    QPoint startPosition(x(), y());
    QPoint endPosition((x()+d_x), (y()+d_y));

    QPropertyAnimation *s_a = new QPropertyAnimation(this, "getPosition");
    s_a->setStartValue(startPosition);
    s_a->setDuration(100);
    s_a->setEndValue(endPosition);
    s_a->start();

    if(typeMap == MAP_TARGET)
        connect(s_a, SIGNAL(finished()), this, SLOT(setGoodAndCheck()));
    else
        connect(s_a, SIGNAL(finished()), this, SLOT(unSetGood()));
}

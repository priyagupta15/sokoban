#include "player.h"
#include "game.h"
#include "map.h"
#include "cell.h"

#include <QPropertyAnimation>

extern Game * game;

void Player::keyPressEvent(QKeyEvent *event)
{
    if(game->map->isLevelFinished())
        return;

    int d_x = 0;
    int d_y = 0;
    int oldx = x();
    int oldy = y();

    switch(event->key())
    {
    case Qt::Key_E:
        game->nextLevel();
        return;
    case Qt::Key_R:
    case Qt::Key_Space:
        game->restartLevel();
        return;

    case Qt::Key_Left:
    case Qt::Key_A:
        d_x = -64;
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
         d_x = 64;
        break;

    case Qt::Key_Up:
    case Qt::Key_W:
         d_y = -64;
        break;

    case Qt::Key_Down:
    case Qt::Key_S:
         d_y = 64;
        break;
    }

    if(!canMove) return;

    if(game->map->getCellByPos(oldx+d_x, oldy+d_y)->getType() == MAP_WALL)
        return;

    Stone *st = game->map->getStoneByPos(oldx+d_x, oldy+d_y);
    if(st != nullptr)
    {
        if(game->map->isStoneAtPos(oldx+(2*d_x), oldy+(2*d_y))) return;

        int typeMap = game->map->getCellByPos(oldx+(2*d_x), oldy+(2*d_y))->getType();

        switch(typeMap)
        {
            case MAP_WALL:
                return;
            case MAP_TARGET:
            case MAP_FLOOR:
            st->animateStone(d_x, d_y, typeMap);

            break;
        }
    }

    canMove = false;

    this->animate(d_x, d_y);
}

void Player::animate(int d_x, int d_y)
{
    QPoint startPosition(x(), y());
    QPoint endPosition((x()+d_x), (y()+d_y));

    QPropertyAnimation *a = new QPropertyAnimation(this, "getPosition");
    a->setStartValue(startPosition);
    a->setDuration(100);
    a->setEndValue(endPosition);
    a->start();

    connect(a, SIGNAL(finished()), this, SLOT(allowMove()));
}

void Player::allowMove()
{
    canMove = true;
}

QPoint Player::getPosition() const
{
    return QPoint(x(), y());
}

void Player::setPosition(QPoint p)
{
    setPos(p);
}

Player::Player(int x, int y) :
    QObject(),
    QGraphicsPixmapItem()
{
    canMove = true;
    setPos(x, y);
    setPixmap(QPixmap(":/images/gfx_sokoban/user.png"));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    setZValue(10);//display over other items
}

void Player::focusOutEvent(QFocusEvent* e)
{
    setFocus();
}


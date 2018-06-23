#include "cell.h"

Cell::Cell(int x, int y, QString text, int t) :
    QGraphicsPixmapItem()
{
    type = t;
    setPixmap(text);
    setPos(x, y);

}

int Cell::getType() const
{
    return type;
}

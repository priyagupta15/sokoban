#ifndef CELL_H
#define CELL_H

#include <QGraphicsPixmapItem>


class Cell : public QGraphicsPixmapItem
{
private:
    int type;
public:
    Cell(int x, int y, QString txt, int t);
    int getType() const;
};

#endif // CELL_H

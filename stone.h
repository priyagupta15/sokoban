#ifndef STONE_H
#define STONE_H


#include <QGraphicsPixmapItem>
#include <QObject>


class Stone : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPoint getPosition READ getPosition WRITE setPosition)

public slots:
    void unSetGood();
    void setGoodAndCheck();
public:
    QPoint getPosition() const;
    void setPosition(QPoint p);
    Stone(int x, int y);
    void setGood();
    void animateStone(int x, int y, int type);

    bool good;
};

#endif // STONE_H

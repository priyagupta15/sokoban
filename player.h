#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QObject>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPoint getPosition READ getPosition WRITE setPosition)
public slots:
    void allowMove();

public:
    bool canMove;

    Player(int x, int y);
    QPoint getPosition() const;
    void setPosition(QPoint p);
    void animate(int d_x, int d_y);
    void keyPressEvent(QKeyEvent *e);
    void focusOutEvent(QFocusEvent* e);
};

#endif // PLAYER_H

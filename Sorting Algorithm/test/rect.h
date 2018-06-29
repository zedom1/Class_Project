#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPoint>
#include <iostream>



class Rect : public QGraphicsItem
{


public:
    Rect();
    Rect(int x, int y, int l);
    QRectF boundingRect() const;

    enum selectMode {NORMAL, SELECTED, MAXN, SWAP} ;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setColorMode(selectMode mode);

private:
    int width;
    int length;
    selectMode colorMode;

public:
    selectMode getColorMode();

};

#endif // RECTANGLE_H

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
    Rect(double x, double y, double l);
    QRectF boundingRect() const;

    enum selectMode {NORMAL, SELECTED, MAXN, SWAP,FINISHED,PIVOT, TOLS} ;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setColorMode(selectMode mode);
    selectMode getColorMode();

private:
    int width;
    int length;
    selectMode colorMode;

};

#endif // RECTANGLE_H

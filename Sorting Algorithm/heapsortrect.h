#ifndef HEAPSORTRECT_H
#define HEAPSORTRECT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QRectF>
#include <QString>

class heapsortRect: public QGraphicsItem
{
public:
    heapsortRect(int,int,int);
    QRectF boundingRect() const;

    enum selectMode {NORMAL, SELECTED, MAXN, SWAP,FINISHED} ;

    void paint(QPainter *,const QStyleOptionGraphicsItem *,QWidget *);
    void setColorMode(selectMode mode);
    selectMode getColorMode();

//private:
    int val;
    int width;
    int length;
    selectMode colorMode;
};

#endif // HEAPSORTRECT_H

#ifndef ITEMFORR_H
#define ITEMFORR_H
#include "rect.h"
#include <QGraphicsItem>

class ItemForR
{
public:
    ItemForR(int num, int index, int aa);
    ItemForR(int num, int index, int aa, int hight);
    ~ItemForR();
    Rect *rect;
    QGraphicsTextItem *text;
    int num;
    int index;
    int current;
    int x,y;

    void move(double x, double y);
};


#endif // ITEMFORR_H

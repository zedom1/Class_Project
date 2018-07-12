#ifndef ITEM_H
#define ITEM_H
#include "rect.h"
#include <QGraphicsItem>
class Item
{
public:
    Item(int num, int index, int aa);
    Item();
    ~Item();
    Rect *rect;
    QGraphicsTextItem *text;
    int num;

    void move(double x, double y);
};

#endif // ITEM_H

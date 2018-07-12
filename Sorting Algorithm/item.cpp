#include "item.h"

Item::Item(int num, int index, int aa)
{
    this->rect = new Rect( 100.0+40.0*index , 120.0, aa*1.0 );
    this->text = new QGraphicsTextItem(QString::number(num));
    text->setPos(210.0+80.0*index,260.0);
    QFont font("Arial");
    font.setPointSizeF(15.0);
    text->setFont(font);
    this->num = num;
}

Item::Item()
{
    rect = nullptr;
    text = nullptr;
    num = 0;
}

Item::~Item()
{
    delete rect;
    delete text;
}

void Item::move(double x, double y)
{
    rect->moveBy(x,y);
    text->moveBy(x*2,y);
}

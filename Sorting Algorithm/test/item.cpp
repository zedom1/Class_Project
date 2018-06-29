#include "item.h"

Item::Item(int num, int index, int aa)
{
    this->rect = new Rect( 200.0+40.0*index , 120.0, aa*1.0 );
    this->text = new QGraphicsTextItem(QString::number(num));
    text->setPos(410.0+80.0*index,260.0);
    QFont font("Arial");
    font.setPointSizeF(15.0);
    text->setFont(font);
    this->num = num;
}

Item::~Item()
{
    if( rect != nullptr )
        delete rect;
}

void Item::move(double x, double y)
{
    rect->moveBy(x,y);
    text->moveBy(x*2,y);
    /*
    if(x>0.0)
        text->moveBy(x+5,y);
    else
        text->moveBy(x-5,y);*/
}

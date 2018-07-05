#include "itemforr.h"

ItemForR::ItemForR(int num, int index, int aa)
{
    this->rect = new Rect( 100.0+40.0*(index%10), 100+20*(index/10), aa );
    this->text = new QGraphicsTextItem(QString::number(num));
    text->setPos(210.0+80.0*(index%10),168.0+40*(index/10));
    QFont font("Arial");
    font.setPointSizeF(15.0);
    text->setFont(font);
    this->num = num;
    current=index;
    this->x=index;
    this->y=50;
}

ItemForR::ItemForR(int num, int index, int aa, int hight)
{
    this->rect = new Rect( 100.0+40.0*index, 120+20*((hight-1)/10) , aa );
    this->rect->setColorMode(Rect::TOLS);
    this->text = new QGraphicsTextItem(QString::number(num));
    text->setPos(210.0+80.0*index , 208+40*((hight-1)/10) );
    QFont font("Arial");
    font.setPointSizeF(15.0);
    text->setFont(font);
    this->num = num;
    this->x=100.0+40.0*index;
    this->y=120+20*(hight/10);
}

ItemForR::~ItemForR()
{
    if( rect != nullptr )
        delete rect;
    if( text != nullptr )
        delete text;
}

void ItemForR::move(double x, double y)
{
    rect->moveBy(x,y);
    text->moveBy(x*2,y*2);
    /*
    if(x>0.0)
        text->moveBy(x+5,y);
    else
        text->moveBy(x-5,y);*/
}

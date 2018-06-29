#include "rect.h"

Rect::Rect()
{
    width = 50;
    length = 100;
    this->setX(250);
    this->setY(50);
    colorMode = NORMAL;
}

Rect::Rect(int x, int y, int l=100)
{
    width = 50;
    length = l;
    this->setX(x);
    this->setY(y);
    colorMode = NORMAL;
}

QRectF Rect::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(this->x() - penWidth / 2, this->y() - penWidth / 2,
                  width + penWidth, length + penWidth);
}

void Rect::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setWidth(2);
    switch(colorMode){
    case NORMAL:
        painter->setBrush(QColor(62, 188, 202, 200));
        break;
    case SWAP:
        painter->setBrush(QColor(255,0,0,200));
        break;
    case SELECTED:
        painter->setBrush(QColor(0,255,0,200));
        break;
    case MAXN:
        painter->setBrush(QColor(0,0,255,200));
        break;
    }
    painter->setPen(pen);
    painter->drawRect(this->x(), this->y()-length, width ,length);
}

void Rect::setColorMode(selectMode mode)
{
    colorMode = mode;
}

Rect::selectMode Rect::getColorMode()
{
    return colorMode;
}

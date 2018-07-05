#include "heapsortrect.h"

#include <QFont>
#include <QString>

heapsortRect::heapsortRect(int x,int y,int v)
{
    width=30;
    length=30;

    this->setX(x);
    this->setY(y);
    val=v;

    colorMode=NORMAL;
}

QRectF heapsortRect::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(this->x() - penWidth / 2, this->y() - penWidth / 2,
                  width + penWidth, length + penWidth);
}

void heapsortRect::paint(QPainter *painter,
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
    case FINISHED:
        painter->setBrush(QColor(255,0,127,127));
        break;
    }
    painter->setPen(pen);
    painter->drawRect(this->x(), this->y(), width ,length);

    QString s=QString::number(val,10);
    QFont font=painter->font();
    font.setPixelSize(20);
    painter->setFont(font);
    qreal penWidth = 1;
    painter->drawText(this->x() - penWidth / 2, this->y() - penWidth / 2, width + penWidth, length + penWidth,Qt::AlignCenter,s);

}

void heapsortRect::setColorMode(selectMode mode)
{
    colorMode = mode;
}

heapsortRect::selectMode heapsortRect::getColorMode()
{
    return colorMode;
}

#ifndef SORTALGORITHM_H
#define SORTALGORITHM_H
#include "widget.h"
#include "item.h"
#include "recordlist.h"
#include "event.h"

#include <QApplication>
#include <QtCore>
#include <QObject>
#include <QtWidgets>
#include <iostream>
#include <algorithm>

class SortAlgorithm
{
private:
    static SortAlgorithm* algorithm;
protected:
    SortAlgorithm();
public:
    static QGraphicsScene *scene;
    static void setAlgorithm(SortAlgorithm* algo);
    static SortAlgorithm* getInstance();
    virtual void restart()=0;
    virtual SortAlgorithm* resetAlgorithm(int num=0, int * array=nullptr)=0;
};

#endif // SORTALGORITHM_H

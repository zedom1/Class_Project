#ifndef OPERATOR_H
#define OPERATOR_H

#include "item.h"
#include "recordlist.h"
#include "widget.h"
#include <iostream>
#include <algorithm>
#include <QTime>
#include <QApplication>
#include <QTimer>
#include <QTimerEvent>
#include <QtCore>
#include <QObject>
#include <QtWidgets>
#include <QWidget>

class Processor: public QObject
{

public:
    static Processor* getProcessor(Widget * widget = NULL);
    static const int totalCount = 15;
    Processor* resetProcessor(int num, int * array);
    ~Processor();

    Item ** itemList = NULL;
    int numItem;
    QGraphicsScene *scene = NULL;
    RecordList * recordList = NULL;
    QTimer *counter = NULL;
    int id;
    int count;
    int index1,index2;

    void addItem();
    void handleArray(int *array);
    void swap();
    void getRecord();
    void handleRecord();
    //static Widget * getWidget();

private:
    Processor( Widget * widget = NULL, int num=0, int*array=nullptr );
    static Processor *processor;
    static Widget * wid;

private slots:
    void timerUpdate();
    void update();
};

void sleep(unsigned int msec);

#endif // OPERATOR_H

#ifndef OPERATOR_H
#define OPERATOR_H

#include "item.h"
#include "recordlist.h"
#include "widget.h"
//#include <QWidget>
#include "event.h"
#include <iostream>
#include <algorithm>
#include <QApplication>
#include <QtCore>
#include <QObject>
#include <QtWidgets>

class Processor: public QObject
{

public:
    static Processor* getProcessor(Widget * widget = NULL);
    static const int totalCount = 20;
    Processor* resetProcessor(int num, int * array = nullptr);
    ~Processor();

    Item ** itemList = NULL;
    int numItem;
    RecordList * recordList = NULL;

    int count;
    int index1,index2;

    void addItem();
    void handleArray(int *array);
    void swap();
    void getRecord();
    void handleRecord();
    //static Widget * getWidget();
    static QGraphicsScene *scene;

private:
    Processor( Widget * widget = NULL, int num=0, int*array=nullptr );
    static Processor *processor;
    static Widget * wid;


    class Cleaner{
    public:
        ~Cleaner() {
            if (Processor::processor){
                delete Processor::processor;
                Processor::processor = nullptr;
            }
        }
    };
    static Cleaner cn;

private slots:
    void update();
};

void sleep(unsigned int msec);

#endif // OPERATOR_H

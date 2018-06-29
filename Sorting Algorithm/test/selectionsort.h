#ifndef OPERATOR_H
#define OPERATOR_H

#include "item.h"
#include "recordlist.h"
#include "widget.h"
#include "sortalgorithm.h"
//#include <QWidget>
#include "event.h"
#include <iostream>
#include <algorithm>
#include <QApplication>
#include <QtCore>
#include <QObject>
#include <QtWidgets>

class SelectionSort : public QObject, public SortAlgorithm
{

public:
    static SelectionSort* getInstance(Widget * widget = NULL);
    static const int totalCount = 20;
    virtual SelectionSort* resetAlgorithm(int num=0, int * array = nullptr);
    ~SelectionSort();

    Item ** itemList = NULL;
    int numItem;
    RecordList * recordList = NULL;

    int count;
    int index1,index2;

    void addItem();
    void handleArray(int *array);
    void swap();
    void restart();
    void getRecord();
    void handleRecord();
    static QGraphicsScene *scene;

private:
    SelectionSort( Widget * widget = nullptr, int num=0, int*array=nullptr );
    static SelectionSort *selectionSort;
    static Widget * wid;


    class Cleaner{
    public:
        ~Cleaner() {
            if (SelectionSort::selectionSort){
                delete SelectionSort::selectionSort;
                SelectionSort::selectionSort = nullptr;
            }
        }
    };
    static Cleaner cn;

private slots:
    void update();
};

#endif // OPERATOR_H

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "sortalgorithm.h"
//#include <QWidget>


class QuickSort: public QObject,public SortAlgorithm
{

public:
    static QuickSort* getInstance(int mod = 0);
    static const int totalCount = 20;
    virtual void remove();
    virtual QuickSort* resetAlgorithm(int num=0, int * array = nullptr, int mod = 0 );
    ~QuickSort();

    Item ** itemList = NULL;
    int numItem;
    RecordList * recordList = NULL;

    int count;
    int index1,index2;

    void addItem();
    void handleArray(int *array);
    void swap();
    void restart();
    void quickSort(int *temarray,int start,int end);
    void getRecord();
    void handleRecord();

private:
    QuickSort( int num=0, int*array=nullptr );
    static QuickSort *qSort;

    class Cleaner{
    public:
        ~Cleaner() {
            if (QuickSort::qSort){
                delete QuickSort::qSort;
                QuickSort::qSort = nullptr;
            }
        }
    };
    static Cleaner cn;

};


#endif

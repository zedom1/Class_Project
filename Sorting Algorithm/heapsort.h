#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "heapsortrect.h"
#include "sortalgorithm.h"

class HeapSort: public QObject, public SortAlgorithm
{
public:
    static HeapSort* getInstance(int mod = 0);
    static const int totalCount=10;
    virtual void remove();
    virtual HeapSort* resetAlgorithm(int num, int * array, int mod = 0 ) override;
    ~HeapSort();

    heapsortRect **items=NULL;
    QGraphicsLineItem **lines=NULL;
    int num;
    RecordList *recordList=NULL;

    int count;
    int index1,index2;
    qreal ix1,iy1,ix2,iy2;

    void handleArray(int *arr);
    void addItem();
    void getRecord();
    void buildHeap();
    void swap();
    void handleRecord();
    virtual void restart() override;

private:
    HeapSort(int num=0 ,int *array=NULL);
    static HeapSort *heapSort;
    int *ar;
    int *initar;

    class Cleaner{
    public:
        ~Cleaner() {
            if (HeapSort::heapSort){
                delete HeapSort::heapSort;
                HeapSort::heapSort = nullptr;
            }
        }
    };
    static Cleaner cn;

};

#endif

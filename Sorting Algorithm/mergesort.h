#ifndef MERGESORT_H
#define MERGESORT_H

#include "sortalgorithm.h"

class MergeSort: public QObject, public SortAlgorithm
{

public:
    static MergeSort* getInstance();
    static const int totalCount = 20;
    virtual void remove();
     virtual MergeSort* resetAlgorithm(int num=0, int * array = nullptr);
    //Processor* resetProcessor(int num, int * array = nullptr);
    ~MergeSort();

    Item ** itemList = NULL;
    int numItem;
    RecordList * recordList = NULL;

    int count;
    int index1,index2;

    void addItem();
    void handleArray(int *array);
    void swap();
    void restart();
    void moveDown();
    void merge();
    void quickSort(int *temarray,int start,int end);
     void Sort(int *arr, int l, int m, int r,Item**tem);
    void mergeSort(int *a,int x, int y,Item**tem);

    void getRecord();
    void handleRecord();
    //static Widget * getWidget();
    //static QGraphicsScene *scene;

private:
    MergeSort( int num=0, int*array=nullptr );
    static MergeSort *mSort;


    class Cleaner{
    public:
        ~Cleaner() {
            if (MergeSort::mSort){
                delete MergeSort::mSort;
                MergeSort::mSort = nullptr;
            }
        }
    };
    static Cleaner cn;
};



#endif // OPERATOR_H

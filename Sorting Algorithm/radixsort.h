#ifndef RADIXSORT_H
#define RADIXSORT_H

#include "sortalgorithm.h"

class RadixSort : public QObject, public SortAlgorithm
{

public:
    static RadixSort* getInstance();
    static const int totalCount = 10;
    virtual void remove();
    virtual RadixSort* resetAlgorithm(int num=0, int * array = nullptr);
    ~RadixSort();

    ItemForR ** itemList = NULL;
    ItemForR ** slotList = NULL;
    int numItem;
    RecordList * recordList = NULL;

    int count = 0;
    int index1,index2;
    int top=0;

    void addItem();
    void handleArray(int *array);
    void swap();
    void topcheck();
    void restart();
    void getRecord();
    void handleRecord();


private:
    RadixSort( int num=0, int*array=nullptr );
    static RadixSort *radixsort;

    class Cleaner{
    public:
        ~Cleaner() {
            if (RadixSort::radixsort){
                delete RadixSort::radixsort;
                RadixSort::radixsort = nullptr;
            }
        }
    };
    static Cleaner cn;

};
#endif // RADIXSORT_H

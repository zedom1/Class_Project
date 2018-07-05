#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "sortalgorithm.h"

class BubbleSort : public QObject, public SortAlgorithm
{

public:
    static BubbleSort* getInstance(int mod = 0);
    static const int totalCount = 20;
    virtual void remove();
    virtual BubbleSort* resetAlgorithm(int num=0, int * array = nullptr, int mod = 0 );
    ~BubbleSort();

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


private:
    BubbleSort( int num=0, int*array=nullptr );
    static BubbleSort *bubblesort;

    class Cleaner{
    public:
        ~Cleaner() {
            if (BubbleSort::bubblesort){
                delete BubbleSort::bubblesort;
                BubbleSort::bubblesort = nullptr;
            }
        }
    };
    static Cleaner cn;

};
#endif // BUBBLESORT_H

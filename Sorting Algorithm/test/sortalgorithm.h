#ifndef SORTALGORITHM_H
#define SORTALGORITHM_H
#include "widget.h"

class SortAlgorithm
{
private:
    static SortAlgorithm* algorithm;
protected:
    SortAlgorithm();
public:
    static void setAlgorithm(SortAlgorithm* algo);
    static SortAlgorithm* getInstance();
    virtual void restart()=0;
    virtual SortAlgorithm* resetAlgorithm(int num=0, int * array=nullptr)=0;
};

#endif // SORTALGORITHM_H

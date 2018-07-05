#ifndef RECORD_H
#define RECORD_H
#include "item.h"

/*
 * type:
 *    0: color
 *    1: swap
 *
 * type 0 :
 *
 *    attribute1:
 *        0: normal color
 *        1: compare color
 *        2: maxn color
 *        3: if not maxn, then normal color
 *
 *    attribute2:
 *        the rect index
 */

class Record
{
public:
    int type;
    int attribute1;
    int attribute2;

    Record * succ;
    Record * pred;
    Item **a;
    Item **b;
    Record(int type, int i1, int i2, Record* pre=nullptr, Record* s = nullptr);
    Record(int type, int i1, int i2,Item **a,Item **b,Record* pre, Record* s);
    Record(int type,int i1,int i2,Item **a,Item**b);
    Record();
};

#endif // RECORD_H

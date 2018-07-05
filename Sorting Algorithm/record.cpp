#include "record.h"

Record::Record()
{
    pred = nullptr;
    succ = nullptr;
    type = -1;
    attribute1 = attribute2 = 0;
}

Record::Record(int type, int i1, int i2, Record* pre, Record* s)
{
    succ = s;
    pred = pre;
    this->type = type;
    attribute1 = i1;
    attribute2 = i2;
}

Record::Record(int type, int i1, int i2,Item **a,Item**b,Record* pre, Record* s)
{
    succ = s;
    pred = pre;
    this->type = type;
    attribute1 = i1;
    attribute2 = i2;
    this->a=a;
    this->b=b;
}
Record::Record(int type,int i1,int i2,Item** a,Item**b)
{
    this->type=type;
    attribute1=i1;
    attribute2=i2;
    this->a=a;
     this->b=b;
}


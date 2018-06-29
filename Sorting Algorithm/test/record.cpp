#include "record.h"

Record::Record()
{
    pred = nullptr;
    succ = nullptr;
}

Record::Record(int type, int i1, int i2, Record* pre, Record* s)
{
    succ = s;
    pred = pre;
    this->type = type;
    attribute1 = i1;
    attribute2 = i2;
}
Record::Record(int type, int i1, int i2,Item **a,Record* pre, Record* s)
{
    succ = s;
    pred = pre;
    this->type = type;
    attribute1 = i1;
    attribute2 = i2;
    this->a=a;
}
Record::Record(int type,int i1,int i2,Item** a)
{
    this->type=type;
    attribute1=i1;
    attribute2=i2;
    this->a=a;
}

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

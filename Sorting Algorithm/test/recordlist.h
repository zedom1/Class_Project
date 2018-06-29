#ifndef RECORDLIST_H
#define RECORDLIST_H
#include "record.h"

class RecordList
{
    Record * header;
    Record * trailer;
public:
    int size;
    Record * current;
    RecordList();
    ~RecordList();
    void addRecord(Record * record);
    void addRecord(int type, int a1, int a2);
    void move(int mod=0);
    void clear();
    bool empty();
};

#endif // RECORDLIST_H

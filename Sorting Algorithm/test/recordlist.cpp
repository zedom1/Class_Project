#include "recordlist.h"
#include <iostream>
RecordList::RecordList()
{
    size = 0;
    header = new Record();
    trailer = new Record();
    header->succ = trailer;
    header->type = trailer->type = -1;
    trailer->pred = header;
    current = nullptr;
}

void RecordList::addRecord(Record * record)
{
    record->pred = trailer->pred;
    record->succ = trailer;
    trailer->pred->succ = record;
    trailer->pred = record;
    size++;
    if(size==1){
        //std::cout<<"set current\n";
        current = record;
    }
}

void RecordList::addRecord(int type, int a1, int a2)
{
    Record * r = new Record(type, a1, a2);
    addRecord(r);
}

void RecordList::move(int mod)
{
    if(mod==0)
        current = current->succ;
    else
        current = current->pred;
}

RecordList::~RecordList()
{
    if(header==nullptr&&trailer==nullptr)
        return;
    clear();
    delete header;
    delete trailer;
}

void RecordList::clear()
{
    Record* t1 = header->succ;
    Record* t2 = t1->succ;
    while(t1!=trailer){
        delete t1;
        t1 = t2;
        t2 = t2->succ;
    }
}

bool RecordList::empty()
{
    return size==0;
}

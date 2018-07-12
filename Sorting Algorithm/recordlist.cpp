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
    Record * r = new Record(type, a1, a2,trailer->pred,trailer);
    this->trailer->pred->succ = r;
    this->trailer->pred = r;
    this->size++;
    if(this->size==1){
        //std::cout<<"set current\n";
        this->current = r;
    }
}

void RecordList::addRecord(int type, int a1, int a2,Item** a,Item** b)
{
    Record * r = new Record(type, a1, a2,a,b,trailer->pred,trailer);
    this->trailer->pred->succ = r;
    this->trailer->pred = r;
    this->size++;
    if(this->size==1){
        //std::cout<<"set current\n";
        this->current = r;
    }

}
Record * RecordList::move(int mod)
{
    if(mod==0)
        //if(current->succ != trailer)
            current = current->succ;
    else
        //if(current->pred != header)
            current = current->pred;
    return current;
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
    if(empty())
        return;
    Record* t1 = header->succ;
    Record* t2 = t1->succ;
    while( t1!=trailer && t2!=nullptr ){
        delete t1;
        t1 = t2;
        t2 = t2->succ;
    }
    header->succ = trailer;
    trailer->pred = header;
    size = 0;
}

bool RecordList::empty()
{
    return size==0;
}

bool RecordList::atHeader()
{
    return current==header;
}

bool RecordList::atTrailer()
{
    return current==trailer;
}


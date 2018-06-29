#include "processor.h"

Processor * Processor::processor = NULL;
Widget * Processor::wid = NULL;

Processor::Processor(Widget * widget, int num, int*array)
{
    scene = new QGraphicsScene;
    numItem = (num==0)? qrand()%3+3 : num;
    count = 0;
    if(widget)
        wid = widget;
    handleArray(array);
    if(recordList)
        delete recordList;
    recordList = new RecordList();
    getRecord();
    std::cout<<numItem<<std::endl;
    counter = new QTimer(this);
    connect(counter,&QTimer::timeout, this,&Processor::swap);
    //counter->start(60);
    //view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,1200,700);
    connect(scene, &QGraphicsScene::changed, this, &Processor::update);

    addItem();

    QTimer *c1 = new QTimer(this);
    c1->start(1000);
    connect(c1, &QTimer::timeout, this, &Processor::handleRecord);
}

void Processor::handleArray(int *array)
{
    int minx = 100;
    int maxn = 0;
    int * temarray;
    itemList = new Item* [numItem];
    if(array==nullptr)
    {
        temarray = new int[numItem];
        for(int i=0; i<numItem; i++){
            temarray[i] = qrand()%10+5;
        }
    }
    else
        temarray = array;
    //std::cout<<numItem<<std::endl;
    for(int i=0; i<numItem; i++){

        minx = std::min(minx, temarray[i]);
        maxn = std::max(maxn, temarray[i]);
        //std::cout<<temarray[i]<<std::endl;
    }

    for(int i=0; i<numItem; i++){
        int aa = (int)((temarray[i]-minx+1)*1.0/(maxn-minx)*110);
        itemList[i] = new Item(temarray[i],i, aa);
        //std::cout<<aa<<std::endl;
    }
    delete []temarray;
}

Processor* Processor::getProcessor(Widget * widget)
{
    if(processor == nullptr)
        processor = new Processor(widget);
    return processor;
}

Processor* Processor::resetProcessor(int num, int * array)
{
    if(processor!= nullptr)
        delete processor;
    processor = new Processor(Processor::wid, num, array);
    if(!recordList->empty())
        recordList->clear();
    return processor;
}

void Processor::addItem(){
    scene->addWidget(wid);
    for(int i=0; i<numItem; ++i){
        scene->addItem(itemList[i]->rect);
        scene->addItem(itemList[i]->text);
    }
}

void Processor::update()
{
    this->scene->update(this->scene->sceneRect());
}

void Processor::timerUpdate()
{
    //return;
    count++;
    if(count<totalCount){
        if(itemList[0]->rect->pos().x()<300){
            itemList[0]->move(5,0);
        }
    }
    else{
        counter->stop();
        count = 0;
    }
}

void Processor::swap()
{
    if(count==0){
        itemList[index1]->rect->setColorMode(Rect::SWAP);
        itemList[index2]->rect->setColorMode(Rect::SWAP);
    }
    count++;
    if(count<totalCount){
        //std::cout<<1111<<std::endl;
        Item *item1 = itemList[index1];
        Item *item2 = itemList[index2];
        item1->move( (40*(index2-index1)*1.0)/totalCount, 0 );
        item2->move( (40*(index1-index2)*1.0)/totalCount, 0 );
    }
    else{
        counter->stop();
        count = 0;
        itemList[index1]->rect->setColorMode(Rect::NORMAL);
        itemList[index2]->rect->setColorMode(Rect::NORMAL);
        Item * tem = itemList[index1];
        itemList[index1] = itemList[index2];
        itemList[index2] = tem;
    }
}

void Processor::getRecord()
{
    //if(!recordList->empty())
    //    return;
    int maxn = 0;
    int maxindex = 0;
    //std::cout<<222<<std::endl;
    int * temarray = new int[numItem];
    int tem;
    for(int i=0; i<numItem ; i++)
        temarray[i] = itemList[i]->num;

    for(int i=0; i<numItem; i++){
        maxn = temarray[i];
        maxindex = i;
        recordList->addRecord(0,2,i);
        for(int j=i+1; j<numItem; j++){
            recordList->addRecord(0,1,j);
            if(temarray[j] < maxn){
                recordList->addRecord(0,0,maxindex);
                maxn = temarray[j];
                maxindex = j;
                recordList->addRecord(0,2,j);               
            }
        }
        recordList->addRecord(0,3,numItem-1);
        recordList->addRecord(1,i,maxindex);
        tem = temarray[maxindex];
        temarray[maxindex] = temarray[i];
        temarray[i] = tem;
    }
    delete []temarray;
}

void Processor::handleRecord()
{
    //return;
    Record* record = recordList->current;
    if( !record || record->type==-1 ){
        //std::cout<<"empty"<<std::endl;
        return;
    }
    //std::cout<<11<<std::endl;
    recordList->move();
    if(record->type==1){
        index1 = record->attribute1;
        index2 = record->attribute2;
        counter->start(20);
        //sleep(60);
    }
    /*  0: normal color
     *  1: compare color
     *  2: maxn color
     *  3: if not maxn, then normal color
    */
    else{
        Rect * item = itemList[record->attribute2]->rect;
        switch(record->attribute1){
        case 0:
            item->setColorMode(Rect::NORMAL);
            break;
        case 1:
            item->setColorMode(Rect::SELECTED);
            if(record->attribute2-1>=0 && itemList[record->attribute2-1]->rect->getColorMode()!=Rect::MAXN)
                itemList[record->attribute2-1]->rect->setColorMode(Rect::NORMAL);
            break;
        case 2:
            item->setColorMode(Rect::MAXN);
            break;
        case 3:
            if(item->getColorMode()!=Rect::MAXN)
                item->setColorMode(Rect::NORMAL);
            break;
        }
        //sleep(100);
    }
}

Processor::~Processor()
{
    if(processor)
        delete processor;
    if(itemList){
        for(int i=0; i<numItem; i++)
            delete itemList[i];
        delete []itemList;
    }
    if(scene)
        delete scene;
    if(recordList)
        delete recordList;
    if(counter)
        delete counter;
}

void sleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    while(reachTime<QTime::currentTime())
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

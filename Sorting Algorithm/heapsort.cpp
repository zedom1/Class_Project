#include "heapsort.h"

HeapSort *HeapSort::heapSort = nullptr;

HeapSort::HeapSort(int num,int *array)
{

    if(num==0)
        this->num=10+qrand()%20;
    else
        this->num=num;

    count=0;

    initar=new int[this->num+1];
    ar=new int[this->num+1];
    ar[0]=0;
    initar[0]=0;
    if(array==NULL)
    {
        for(int i=1;i<this->num+1;++i)
        {
            ar[i]=qrand()%100+1;
            initar[i]=ar[i];
        }
    }
    else
    {
        for(int i=1;i<this->num+1;++i)
        {
            ar[i]=array[i-1];
            initar[i]=ar[i];
        }
    }
    handleArray(initar);

    //如果留有之前的记录，则清空
    if(recordList)
        delete recordList;

    recordList=new RecordList();
    getRecord();
    addItem();

    Event *event=Event::getEvent();
    connect(event->swapTimer,&QTimer::timeout,this,&HeapSort::swap);
    connect(event->wholeTimer,&QTimer::timeout,this,&HeapSort::handleRecord);

}

void HeapSort::remove()
{
    delete heapSort;
    heapSort = nullptr;
}

HeapSort* HeapSort::getInstance()
{
    if(heapSort == nullptr )
        heapSort = new HeapSort();
    return heapSort;
}

//根据arr的数值初始化items列表和lines列表的值及位置
void HeapSort::handleArray(int *arr)
{
    int recDis[6];
    recDis[5]=1;
    for(int i=4;i>=0;--i)
        recDis[i]=recDis[i+1]*2+16;

    items=new heapsortRect *[num+1];
    items[0]=NULL;
    items[1]=new heapsortRect(291,20,arr[1]);

    int ind;

    for(ind=2;ind<num+1;++ind)
    {
        int h=qCeil(qLn(ind+1)/qLn(2));
        int recdis=recDis[h-1];
        qreal halfdis=(recdis+1.1-1.1)/2;
        int pow1=qPow(2.0,h-1.0);
        int pow2=qPow(2.0,h-2.0);

        qreal recx;
        qreal recy;
        int no=ind-pow1;
        if(no<pow2)
            recx=299.0-halfdis-(pow2-no)*16.0-recdis*(pow2-no-1.0);
        else
            recx=299.0+halfdis+(no-pow2+1)*16.0+(no-pow2)*recdis;
        recy=20.0+(16.0+20.0)*(h-1);
        items[ind]=new heapsortRect(recx,recy,arr[ind]);
    }

    lines=new QGraphicsLineItem *[num+1];
    lines[0]=NULL;
    lines[1]=NULL;
    for(int ind=2;ind<num+1;++ind)
    {
        int lx1,ly1,lx2,ly2;
        int father=ind/2;
        lx1=(items[father]->x()+8)*2;
        lx2=(items[ind]->x()+8)*2;
        ly1=(items[father]->y()+16)*2;
        ly2=(items[ind]->y())*2;
        lines[ind]=new QGraphicsLineItem(lx1,ly1,lx2,ly2);
    }
}


HeapSort *HeapSort::resetAlgorithm(int num, int *array)
{
    Event * event = Event::getEvent();
    if(items)
    for(int i=1;i<this->num+1;++i)
    {
        event->scene->removeItem(items[i]);
        delete items[i];
    }
    if(lines)
    for(int i=2;i<this->num+1;++i)
    {
        event->scene->removeItem(lines[i]);
        delete lines[i];
    }
    delete [] items;
    delete [] lines;
    recordList->clear();
    delete [] ar;
    delete [] initar;
    if(num==0)
        this->num=10+qrand()%20;
    else
        this->num=num;

    ar=new int[this->num+1];
    ar[0]=0;

    initar=new int[this->num+1];
    initar[0]=0;
    if(array==NULL)
    {
        for(int i=1;i<this->num+1;++i)
        {
            ar[i]=1+qrand()%100;
            initar[i]=ar[i];
        }
    }
    else
    {
        for(int i=1;i<this->num+1;++i)
        {
            ar[i]=array[i-1];
            initar[i]=ar[i];
        }
    }

    handleArray(initar);
    getRecord();
    addItem();
    return heapSort;
}

void HeapSort::addItem()
{
    Event * event = Event::getEvent();
    for(int i=1;i<num+1;++i)
        event->scene->addItem(items[i]);
    for(int i=2;i<num+1;++i)
        event->scene->addItem(lines[i]);

}

void HeapSort::swap()
{
    if(count==0)
    {
        items[index1]->setColorMode(heapsortRect::SWAP);
        items[index2]->setColorMode(heapsortRect::SWAP);
    }
    ++count;
    if(count<=totalCount)
    {
        heapsortRect *item1=items[index1];
        heapsortRect *item2=items[index2];
        qreal mx1=(ix2-ix1+1.0-1.0)/totalCount;
        qreal my1=(iy2-iy1+1.0-1.0)/totalCount;
        qreal mx2=(ix1-ix2+1.0-1.0)/totalCount;
        qreal my2=(iy1-iy2+1.0-1.0)/totalCount;
        item1->moveBy(mx1,my1);
        item2->moveBy(mx2,my2);
    }
    else
    {
        count=0;
        Event::getEvent()->swapTimer->stop();
        items[index1]->setColorMode(heapsortRect::NORMAL);
        items[index2]->setColorMode(heapsortRect::NORMAL);
        heapsortRect *temp=items[index1];
        items[index1]=items[index2];
        items[index2]=temp;
    }
}

void HeapSort::restart()
{
    Event * event = Event::getEvent();
    for(int i=1;i<num+1;++i)
        event->scene->removeItem(items[i]);

    for(int i=2;i<num+1;++i)
        event->scene->removeItem(lines[i]);

    handleArray(initar);
    addItem();
    Record * current = recordList->move(1);
    while(-1!=current->type)
        current = recordList->move(1);
    recordList->move();
}

void HeapSort::getRecord()
{
    buildHeap(); //建立起始堆
    int n=num;
    for(int index=0;index<num-1;++index)
    {
        //remove max key
        recordList->addRecord(1,1,n);
        int temp=ar[1];
        ar[1]=ar[n];
        ar[n]=temp;
        recordList->addRecord(0,4,n);
        --n;

        //shift
        int k=1;
        int v=ar[1];
        bool isHeap=false;

        while ((!isHeap) && ((k * 2) <= n))
        {
            recordList->addRecord(0,2,k);
            int j = k * 2;
            if (j < n)
                if (ar[j] < ar[j+1])
                    ++j;
            recordList->addRecord(0,1,j);

            if (v >= ar[j])
            {
                recordList->addRecord(0,3,j);
                recordList->addRecord(0,0,k);
                isHeap = true;
            }
            else
            {
                recordList->addRecord(0,0,k);
                recordList->addRecord(1,k,j);
                ar[k] = ar[j];
                k = j;
            }
        }
        ar[k] = v;
    }
    recordList->addRecord(0,4,1);
}

void HeapSort::buildHeap()
{
    for (int i = num/2; i >=1; --i) //遍历父结点，从后往前
    {
        int k = i; //记录起始父结点移动的位置
        int v = ar[k]; //记住起始父结点的值

        bool isHeap = false; //这个父结点处还未建成堆

        while ((!isHeap) && ((k * 2) <= num)) //未建成堆且起始父结点shift以后还有孩子
        {
            recordList->addRecord(0,2,k);
            int j = k * 2; //记录较大的子结点
            if (j < num) //如果k结点有两个孩子
                if (ar[j] < ar[j+1]) //如果右孩子大于左孩子
                    ++j; //令j为大孩子
            recordList->addRecord(0,1,j);

            if (v >= ar[j]) //如果当前父结点大于等于它的大孩子
            {
                recordList->addRecord(0,3,j);
                recordList->addRecord(0,0,k);
                isHeap = true; //这个父结点处就是堆，因为是自底向上所以其底下的都是堆
            }
            else //如果父结点小于大孩子
            {
                recordList->addRecord(0,0,k);
                recordList->addRecord(1,k,j);
                ar[k] = ar[j]; //令父结点为大孩子
                k = j; //令k为大孩子的位置

            }
        }
        ar[k] = v; //把起始父结点放在它最终位置

    }

}

void HeapSort::handleRecord()
{
    Event *event=Event::getEvent();
    event->wholeTimer->stop();

    Record *record=recordList->current;
    if(!record||record->type==-1)
        return;

    recordList->move(); //current往前

    if(record->type==1) //当前处理的record为交换
    {
        if(event->userMode==0)
            event->wholeTimer->start(1000);
        index1=record->attribute1;
        index2=record->attribute2;
        ix1=items[index1]->x();
        ix2=items[index2]->x();
        iy1=items[index1]->y();
        iy2=items[index2]->y();
        event->swapTimer->start(50);
    }
    else if(record->type==0) //当前处理的record为着色
    {
        if(event->userMode==0)
            event->wholeTimer->start(400);
        heapsortRect *item=items[record->attribute2];
        switch (record->attribute1) {
        case 0:
            item->setColorMode(heapsortRect::NORMAL);
            break;
        case 1:
            item->setColorMode(heapsortRect::SELECTED);
            if(record->attribute2 >= 1
                    && items[record->attribute2/2]->getColorMode()!=heapsortRect::MAXN)
                items[record->attribute2/2]->setColorMode(heapsortRect::NORMAL);
            break;
        case 2:
            item->setColorMode(heapsortRect::MAXN);
            break;
        case 3:
            if(item->getColorMode()!=heapsortRect::MAXN)
                item->setColorMode(heapsortRect::NORMAL);
            break;
        case 4:
            item->setColorMode(heapsortRect::FINISHED);
            break;
        }
    }
}

HeapSort::~HeapSort()
{
    if(items)
    {
        Event * event = Event::getEvent();
        for(int i=1; i<num+1; i++){
            event->scene->removeItem(items[i]);
            delete items[i];
        }
        delete []items;
    }
    if(lines)
    {
        Event * event = Event::getEvent();
        for(int i=2;i<num+1;++i){
            event->scene->removeItem(lines[i]);
            delete lines[i];
        }
        delete [] lines;
    }
    delete ar;
    delete recordList;
}

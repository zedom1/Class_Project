#include "radixsort.h"

RadixSort * RadixSort::radixsort = nullptr;

/*
 * RadixSort的构造函数
 * 核心思想：每一个待排序的数组对应一个processor，若数组更新则删掉旧的，换成新的processor
 * 每个processor有自己的scene、recordlist
 * widget作为公用参数，在main里面生成，在这里仅用指针指向它用于向scene里添加
 */
RadixSort::RadixSort(int num, int*array)
{
    numItem = (num==0)? qrand()%9+2 : num;
    count = 0;
    handleArray(array);
    if(recordList)
        delete recordList;
    recordList = new RecordList();
    getRecord();
    addItem();

    Event * event = Event::getEvent();
    connect(event->swapTimer,&QTimer::timeout, this,&RadixSort::swap);
    connect(event->wholeTimer, &QTimer::timeout, this, &RadixSort::handleRecord);

}

/*
 * handleArray：
 *      根据输入的数组初始化矩形和文本
 *      如果输入数组为空则根据numItem随机生成数组内容
 *
 *  数组处理：
 *      最大最小值归一化： 找到数组的最大值和最小值，（每个元素-最小值+1） / （最大值-最小值）
 *      得到的数字在（ 0， 1.几 ）之间， 作为长度的放缩比例
 */
void RadixSort::handleArray(int *array)
{
    int minx = 100;
    int maxn = 0;
    int * temarray;
    itemList = new ItemForR* [numItem];
    slotList = new ItemForR* [10];
    for(int i=0;i<10;i++)
        slotList[i] = new ItemForR( i, i, 30, numItem);
    if(array==nullptr)
    {
        temarray = new int[numItem];
        for(int i=0; i<numItem; i++){
            temarray[i] = qrand()%20+5;
        }
    }
    else
    {
        temarray = new int[numItem];
        for(int i=0;i<numItem;i++){
            temarray[i]=array[i];
        }
    }

    for(int i=0; i<numItem; i++){
        minx = std::min(minx, temarray[i]);
        maxn = std::max(maxn, temarray[i]);

    }

    for(int i=0; i<numItem; i++){

        itemList[i] = new ItemForR(temarray[i],i, 30);

    }
    delete []temarray;
}

void RadixSort::remove()
{
    delete radixsort;
    radixsort = nullptr;
}

// RadixSort使用单例模式，此为获得类唯一实例的接口
RadixSort* RadixSort::getInstance()
{
    if(radixsort == nullptr )
        radixsort = new RadixSort();
    return radixsort;
}

// 用户重新设定数组或重新随机初始化之后要调用的函数
RadixSort* RadixSort::resetAlgorithm(int num, int * array)
{
    Event * event = Event::getEvent();
    if(itemList)
    for(int i=0; i<numItem; i++){
        event->scene->removeItem(itemList[i]->rect);
        event->scene->removeItem(itemList[i]->text);
        delete itemList[i];
    }
    delete [] itemList;
    if(slotList)
    for(int i=0; i<10; i++){
        event->scene->removeItem(slotList[i]->rect);
        event->scene->removeItem(slotList[i]->text);
        delete slotList[i];
    }
    delete [] slotList;
    recordList->clear();

    numItem = (num==0)? qrand()%9+2 : num;
    handleArray(array);
    getRecord();
    addItem();

    return radixsort;
}

// 向scene里面添加item
// 要先加widget 即背景、按钮那些，再加矩形、文本等
// 不然widget会把它们覆盖掉
void RadixSort::addItem(){
    Event * event = Event::getEvent();
    for(int i=0; i<numItem; ++i){
        event->scene->addItem(itemList[i]->rect);
        event->scene->addItem(itemList[i]->text);
    }
    for(int i=0; i<10;i++){
        event->scene->addItem(slotList[i]->rect);
        event->scene->addItem(slotList[i]->text);
    }
}


// swap定时器触发之后调用
// 每次移动一小点，count记录当前移动小步的次数
// totalCount记录总共要移动小步的次数
void RadixSort::swap()
{
    count++;
    if(count<=totalCount){

        ItemForR *item1 = itemList[index1];
        if(index2>=1000){ //move into slot
            item1->move( (40*1.0*(index2/1000-(item1->current%10) - 1)*1.0)/totalCount,
                         (40+20*(numItem/10)+20*(index2%1000-(item1->current/10)))/totalCount );
            item1->index=index2;
        }
        else { //remove from slot
            item1->move( -(40*1.0*(item1->index/1000-index2%10 - 1)*1.0)/totalCount,
                         (-(40+20*(numItem/10))-20*(item1->index%1000-index2/10))/totalCount );
            item1->current=index2;
        }
    }
    else{
        count = 0;
        Event::getEvent()->swapTimer->stop();
    }
}

void RadixSort::topcheck()
{
    int* tempA;
    tempA = new int[numItem];
    top = 1;
    int TC = 0;
    while (1)
    {
        TC = 0;
        for (int i = 0; i < numItem; i++)
        {
            int temp = itemList[i]->num;
            for (int p = 0; p < top; p++)
                temp /= 10;
            tempA[i] = temp;
            if (tempA[i] != 0) TC += 1;
        }
        if (TC == 0) break;
        else top++;
    }
}

void RadixSort::restart()
{
    for(int i=0; i<numItem; i++){
        itemList[i]->rect->setX(100+40*itemList[i]->x);
        itemList[i]->rect->setY(itemList[i]->y);
        itemList[i]->text->setPos(210.0+80.0*itemList[i]->x,15+itemList[i]->y);
    }
}

// 实现排序算法的核心函数
// 核心思想：
//      额外开一个数组复制原本内容，使用排序算法对这个数组进行排序，同时记录中间步骤
//      在用户设定好数组后记录就生成了，剩下的演示只是读取生成的记录
void RadixSort::getRecord()
{
    int * temarray = new int[numItem];

    for(int i=0; i<numItem ; i++)
        temarray[i] = i;

    int slot[10][10]={-1};
    int amount[10]={0};

    topcheck();

    for(int t=0;t<top;t++)
    {
        for(int i=0;i<numItem;i++)//get in the slot
        {
            recordList->addRecord(0,1,temarray[i]);
            /* 0: normal color
             * 1: selection color
             * ref:(type 0color, color num, rect index)
             * of (type 1move, index1, index2)
             */
            int R = itemList[temarray[i]]->num;
            for(int p=0;p<t;p++) R/=10;
            R%=10;
            slot[R][amount[R]]=temarray[i];
            amount[R]+=1;
            recordList->addRecord(1,temarray[i],(R+1)*1000+amount[R]-1);
            recordList->addRecord(0,0,temarray[i]);
        }
        int pos=0;
        for(int p=0;p<10;p++)
        {
            for(int j=0;amount[p]>0;amount[p]--,j++)
            {
                //refresh the sequence array
                temarray[pos]=slot[p][j];
                recordList->addRecord(0, 1 ,temarray[pos]);
                recordList->addRecord(1,temarray[pos] ,pos);
                recordList->addRecord(0, 0 ,temarray[pos]);
                pos++;
            }
        }
    }
    delete []temarray;
}

// 演示的核心函数
/*      使用两个timer：
 *          wholeTimer记录上一步到下一步的时间
 *          swapTimer记录交换的时间
 * 记录：
 *      type 1 ： 交换模式
 *          attribute1、2：要交换的两个矩形的index
 *
 *      type 0 ： 上色模式
 *          attribute 0： 颜色模式
 *              0：恢复正常颜色
 *              1：此时矩形被选中，设为选中颜色，若前一个矩形不是最大的，则将前一个矩形恢复成普通颜色（为了去掉上一个矩形的被选中颜色）
 *              2：此时矩形是当前最小，设为最小颜色
 *              3：若矩形不是最小，则恢复成正常颜色
 *          attribute 1： 矩形的index
 */
void RadixSort::handleRecord()
{

    Event * event = Event::getEvent();
    event->wholeTimer->stop();

    Record* record = recordList->current;
    if( !record || record->type==-1 ){

        return;
    }

    recordList->move();

    if(record->type==1){
        if(event->userMode==0)
            event->wholeTimer->start(1000);
        index1 = record->attribute1;
        index2 = record->attribute2;
        event->swapTimer->start(40);
    }
    /*
     *  0: normal color
     *  1: compare color
     *  2: maxn color
     *  3: if not maxn, then normal color
    */
    else{
        if(event->userMode==0)
            event->wholeTimer->start(400);
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
    }
}

RadixSort::~RadixSort()
{
    if(itemList){
        Event * event = Event::getEvent();
        for(int i=0; i<numItem; i++){
            event->scene->removeItem(itemList[i]->rect);
            event->scene->removeItem(itemList[i]->text);
            delete itemList[i];
        }
        delete []itemList;
    }
    if(slotList){
        for(int i=0; i<10; i++)
            delete slotList[i];
        delete []slotList;
    }
    if(recordList)
        delete recordList;
}

#include "quicksort.h"

QuickSort * QuickSort::qSort = nullptr;
Widget * QuickSort::wid = nullptr;

/*
 * Processor的构造函数
 * 核心思想：每一个待排序的数组对应一个processor，若数组更新则删掉旧的，换成新的processor
 * 每个processor有自己的scene、recordlist
 * widget作为公用参数，在main里面生成，在这里仅用指针指向它用于向scene里添加
 */
QuickSort::QuickSort(Widget * widget, int num, int*array)
{
    numItem = (num==0)? qrand()%9+2 : num;
    count = 0;
    if(widget)
        wid = widget;
    handleArray(array);
    if(recordList)
        delete recordList;
    recordList = new RecordList();
    getRecord();
    addItem();

    Event * event = Event::getEvent();
    connect(event->swapTimer,&QTimer::timeout, this,&QuickSort::swap);
    connect(event->wholeTimer, &QTimer::timeout, this, &QuickSort::handleRecord);

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
void QuickSort::handleArray(int *array)
{
    int minx = 100;
    int maxn = 0;
    int * temarray;
    itemList = new Item* [numItem];
    if(array==nullptr)
    {
        temarray = new int[numItem];
        for(int i=0; i<numItem; i++){
            temarray[i] = qrand()%20+5;
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
        double aa = ((temarray[i]-minx+1)*1.0/(maxn-minx)*110);
        itemList[i] = new Item(temarray[i],i, aa);
        //std::cout<<aa<<std::endl;
    }
    delete []temarray;
}

// Processor使用单例模式，此为获得类唯一实例的接口
QuickSort* QuickSort::getInstance(Widget * widget)
{
    if(qSort == nullptr)
        qSort = new QuickSort(widget);
    return qSort;
}

// 用户重新设定数组或重新随机初始化之后要调用的函数
QuickSort* QuickSort::resetAlgorithm(int num, int * array)
{
    for(int i=0; i<numItem; i++){
        scene->removeItem(itemList[i]->rect);
        scene->removeItem(itemList[i]->text);
        delete itemList[i];
    }
    delete [] itemList;
    numItem = (num==0)? qrand()%9+2 : num;
    handleArray(array);
    recordList->clear();
    getRecord();
    addItem();

    return qSort;
}

// 向scene里面添加item
// 要先加widget 即背景、按钮那些，再加矩形、文本等
// 不然widget会把它们覆盖掉
void QuickSort::addItem(){
    if(scene == nullptr){
        scene = new QGraphicsScene;
        scene->setSceneRect(0,0,1200,700);
        connect(scene, &QGraphicsScene::changed, this, &QuickSort::update);
        scene->addWidget(wid);
    }
    for(int i=0; i<numItem; ++i){
        scene->addItem(itemList[i]->rect);
        scene->addItem(itemList[i]->text);
    }
}

void QuickSort::update()
{
    this->scene->update(this->scene->sceneRect());
}

// swap定时器触发之后调用
// 每次移动一小点，count记录当前移动小步的次数
// totalCount记录总共要移动小步的次数
void QuickSort::swap()
{
    if(count==0){
       // itemList[index1]->rect->setColorMode(Rect::SWAP);
       // itemList[index2]->rect->setColorMode(Rect::SWAP);
    }
    count++;
    if(count<=totalCount){
        //std::cout<<1111<<std::endl;
        Item *item1 = itemList[index1];
        Item *item2 = itemList[index2];
        item1->move( (40*1.0*(index2-index1)*1.0)/totalCount, 0 );
        item2->move( (40*1.0*(index1-index2)*1.0)/totalCount, 0 );
    }
    else{
        count = 0;
        Event::getEvent()->swapTimer->stop();
      //  itemList[index1]->rect->setColorMode(Rect::NORMAL);
      //  itemList[index2]->rect->setColorMode(Rect::NORMAL);
        Item * tem = itemList[index1];
        itemList[index1] = itemList[index2];
        itemList[index2] = tem;
    }
}
void QuickSort::restart()
{
    //Record * temrecord = recordList->current;
    Record * current = recordList->move(1);
    Item * tem;
    int index1, index2;
    while(-1!=current->type){
        if(current->type==1){
            index1 = current->attribute1;
            index2 = current->attribute2;
            itemList[index1]->move((40*1.0*(index2-index1)*1.0), 0);
            itemList[index2]->move((40*1.0*(index1-index2)*1.0), 0);
            tem = itemList[index1];
            itemList[index1] = itemList[index2];
            itemList[index2] = tem;
        }
        current = recordList->move(1);
    }
    recordList->move();
    for(int i=0; i<numItem; i++)
        itemList[i]->rect->setColorMode(Rect::NORMAL);
    update();
}

void QuickSort::quickSort(int *temarray,int l,int r)
{
    int temp;
    int tempPivot;
        if (l< r)
        {

            int i = l, j = r, pivot = temarray[l];
            tempPivot=l;
              recordList->addRecord(0,4,i);
            while (i < j)
            {
                while (i < j && temarray[j] >= pivot) // 从右向左找第一个小于x的数
                {
                    recordList->addRecord(0,6,j);
                    j--;
                }
                if (i < j)
                {
                    recordList->addRecord(0,6,j);
                    temp = temarray[i];
                    temarray[i] = temarray[j];
                    temarray[j] = temp;
                    tempPivot=j;
                    recordList->addRecord(1,i,j);
                    i++;
                }
                while (i < j && temarray[i] <= pivot) // 从左向右找第一个大于等于x的数
                {
                    recordList->addRecord(0,5,i);
                    i++;
                }
                if (i < j)
                {
                    recordList->addRecord(0,5,i);
                    temp = temarray[j];
                    temarray[j] = temarray[i];
                    temarray[i] = temp;
                     recordList->addRecord(1,i,j);
                     tempPivot=i;
                    j--;
                }
            }
            recordList->addRecord(0,7,tempPivot);

            quickSort(temarray, l, i - 1); // 递归调用
            quickSort(temarray, i + 1, r);
        }
        else if(l==r){
            recordList->addRecord(0,7,l);
        }
}
// 实现排序算法的核心函数
// 核心思想：
//      额外开一个数组复制原本内容，使用排序算法对这个数组进行排序，同时记录中间步骤
//      在用户设定好数组后记录就生成了，剩下的演示只是读取生成的记录
void QuickSort::getRecord()
{
    int * temarray = new int[numItem];

      for(int i=0; i<numItem ; i++)
          temarray[i] = itemList[i]->num;
      quickSort(temarray,0,numItem-1);
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
void QuickSort::handleRecord()
{
    //return;
    Event * event = Event::getEvent();
    event->wholeTimer->stop();

    Record* record = recordList->current;
    if( !record || record->type==-1 ){
        //std::cout<<"empty"<<std::endl;
        return;
    }
    //std::cout<<11<<std::endl;
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
        case 4://当轮轴值
            item->setColorMode(Rect::PIVOT);
            break;
        case 5:  //从左往右，设置选中。恢复上一个
            item->setColorMode(Rect::SELECTED);
            if(record->attribute2-1>=0&&itemList[record->attribute2-1]->rect->getColorMode()!=Rect::PIVOT&&itemList[record->attribute2-1]->rect->getColorMode()!=Rect::FINISHED)
                itemList[record->attribute2-1]->rect->setColorMode(Rect::NORMAL);
            break;
        case 6://从右往左，设置选中，回复上一个
            item->setColorMode(Rect::SELECTED);
            if(record->attribute2+1 < numItem&&itemList[record->attribute2+1]->rect->getColorMode()!=Rect::PIVOT&&itemList[record->attribute2+1]->rect->getColorMode()!=Rect::FINISHED)
                itemList[record->attribute2+1]->rect->setColorMode(Rect::NORMAL);
            break;
        case 7://已固定的轴值
            item->setColorMode(Rect::FINISHED);
            break;
        }
    }
}

QuickSort::~QuickSort()
{
    if(itemList){
        for(int i=0; i<numItem; i++)
            delete itemList[i];
        delete []itemList;
    }
    if(scene)
        delete scene;
    if(recordList)
        delete recordList;
}

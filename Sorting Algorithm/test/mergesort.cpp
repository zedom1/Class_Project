#include "mergesort.h"

MergeSort * MergeSort::mSort = nullptr;
Widget * MergeSort::wid = nullptr;
/*
 * Processor的构造函数
 * 核心思想：每一个待排序的数组对应一个processor，若数组更新则删掉旧的，换成新的processor
 * 每个processor有自己的scene、recordlist
 * widget作为公用参数，在main里面生成，在这里仅用指针指向它用于向scene里添加
 */
MergeSort::MergeSort(Widget * widget, int num, int*array)
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
    connect(event->swapTimer,&QTimer::timeout, this,&MergeSort::swap);
    connect(event->wholeTimer, &QTimer::timeout, this, &MergeSort::handleRecord);
    connect(event->downTimer,&QTimer::timeout,this,&MergeSort::moveDown);
    connect(event->mergeTimer,&QTimer::timeout,this,&MergeSort::merge);
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
void MergeSort::handleArray(int *array)
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
MergeSort* MergeSort::getInstance(Widget * widget)
{
    if(mSort == nullptr)
        mSort = new MergeSort(widget);
    return mSort;
}

// 用户重新设定数组或重新随机初始化之后要调用的函数
MergeSort* MergeSort::resetAlgorithm(int num, int * array)
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

    return mSort;
}

// 向scene里面添加item
// 要先加widget 即背景、按钮那些，再加矩形、文本等
// 不然widget会把它们覆盖掉
void MergeSort::addItem(){
    if(scene == nullptr){
        scene = new QGraphicsScene;
        scene->setSceneRect(0,0,1200,700);
        connect(scene, &QGraphicsScene::changed, this, &MergeSort::update);
        scene->addWidget(wid);
    }
    for(int i=0; i<numItem; ++i){
        scene->addItem(itemList[i]->rect);
        scene->addItem(itemList[i]->text);
    }
}

void MergeSort::update()
{
    this->scene->update(this->scene->sceneRect());
}

// swap定时器触发之后调用
// 每次移动一小点，count记录当前移动小步的次数
// totalCount记录总共要移动小步的次数
void MergeSort::swap()
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
void MergeSort::merge()
{
    if(count==0){
        itemList[index1]->rect->setColorMode(Rect::SWAP);
       // itemList[index2]->rect->setColorMode(Rect::SWAP);
    }
    count++;
    if(count<=totalCount){
        //std::cout<<1111<<std::endl;
        Item *item1 = itemList[index1];
        //Item *item2 = itemList[index2];
      //  if(index2>index1)
            item1->move( (40*1.0*(index2-index1)*1.0)/totalCount, -100*1.0/totalCount );
    }
    else{
        count = 0;
        Event::getEvent()->mergeTimer->stop();
        itemList[index1]->rect->setColorMode(Rect::NORMAL);
      //  itemList[index2]->rect->setColorMode(Rect::NORMAL);
    }
}
void MergeSort::moveDown()
{
    if(count==0){
        for(int i=index1;i<index2+1;i++)
        {
             itemList[i]->rect->setColorMode(Rect::SWAP);
        }
       }
    count++;
    if(count<=totalCount)
    {
        for(int i=index1;i<index2+1;i++)
        {
            Item *item=itemList[i];
            item->move(0,100*1.0/totalCount);
        }
    }
    else{
        count = 0;
        Event::getEvent()->downTimer->stop();
        for(int i=index1;i<index2+1;i++)
        {
             itemList[i]->rect->setColorMode(Rect::NORMAL);
        }
    }
}
//对数组按序归并
void MergeSort::restart()
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

void MergeSort::Sort(int *arr, int l, int m, int r,Item **tem)
{
    int n1, n2, i, j, k;
    int *left = NULL, *right = NULL;
    Item ** temItemList = new Item* [r-l+1];
    n1 = m - l + 1;
    n2 = r - m;
    left = (int *)malloc(sizeof(int) * (n1));
    right = (int *)malloc(sizeof(int) * (n2));
    for (i = 0; i < n1; i++)  //对左数组赋值
    {
        left[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++)  //对右数组赋值
    {
        right[j] = arr[m + 1 + j];
    }
    i = j = 0;
    k = l;
    while (i < n1 && j < n2) //将数组元素值两两比较，并合并到arr数组
    {
        if (left[i] <= right[j])
           {
            recordList->addRecord(4,i+l,k);
            temItemList[k-l]=tem[i+l];
            arr[k++] = left[i++];//将第（i+l）个块放回第k个位置
           // std::cout<<itemList[i+l]->num;
        }
        else
        {
            recordList->addRecord(4,m+1+j,k);
            temItemList[k-l]=tem[m+1+j];
            arr[k++] = right[j++];//将第（m+1+j）个块放回第k个位置
           // std::cout<<itemList[i+l]->num;
        }
    }

    for (; i < n1; i++) //当左数组有元素剩余时,将剩余元素依次合并到arr数组
    {
         recordList->addRecord(4,i+l,k);
         temItemList[k-l]=tem[i+l];
        arr[k++] = left[i];
       // std::cout<<temItemList[k-l]->num;
    }
    for (; j < n2; j++) //如果右数组有元素剩余，则将剩余元素依次合并到arr数组
    {
         recordList->addRecord(4,m+1+j,k);
         temItemList[k-l]=tem[m+1+j];
        arr[k++] = right[j];
       // std::cout<<temItemList[k-l]->num;
    }
    for(int i=l;i<r+1;i++)
    {
        tem[i]=temItemList[i-l];
    }
    recordList->addRecord(5,l,r,temItemList);//getRecord完成-》tem是一个完全排序的数组！！
    //delete []temItemList;
}
void MergeSort::mergeSort(int *arr, int left, int right,Item **tem)
{
    int mid;

    recordList->addRecord(2,left,right);
    recordList->addRecord(2,left,right);
    if (left<right)
    {
        mid = (int)((left + right) / 2);      //将arr数组分成两半
        mergeSort(arr, left, mid,tem);   //递归拆分左数组
        mergeSort(arr, mid + 1, right,tem); //递归拆分右数组
        recordList->addRecord(3,left,right);
        Sort(arr, left, mid, right,tem);    //合并数组
    }

}
/*
void Processor::quickSort(int *temarray,int l,int r)
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
}*/
// 实现排序算法的核心函数
// 核心思想：
//      额外开一个数组复制原本内容，使用排序算法对这个数组进行排序，同时记录中间步骤
//      在用户设定好数组后记录就生成了，剩下的演示只是读取生成的记录
void MergeSort::getRecord()
{
    int * temarray = new int[numItem];
    Item **tem=new Item*[numItem];
    int *b=new int[numItem];
      for(int i=0; i<numItem ; i++)
      {
          temarray[i] = itemList[i]->num;
          tem[i]=itemList[i];
      }
      mergeSort(temarray,0,numItem-1,tem);
       delete []temarray;
      delete []b;
      delete []tem;
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
void MergeSort::handleRecord()
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
    else if(record->type==5)
    {
        if(event->userMode==0)
            event->wholeTimer->start(1000);
        int l=record->attribute1;
        int r=record->attribute2;
        for(int i=l;i<r+1;i++)
        {
            itemList[i]=record->a[i-l];
        }
    }
    else if(record->type==4)
    {
        if(event->userMode==0)
            event->wholeTimer->start(1000);

        index1 = record->attribute1;
        index2 = record->attribute2;
        event->mergeTimer->start(40);
    }
    else if(record->type==3)
    {
        if(event->userMode==0)
            event->wholeTimer->start(1000);
        //int *index=new int[record->attribute2-record->attribute1+1];
       /* for(int i=record->attribute1;i<record->attribute2+1;i++)
        {
            index[i]=
        }*/
        index1 = record->attribute1;
        index2 = record->attribute2;
        event->downTimer->start(40);
    }
    else if(record->type==0){
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
        case 5:  //从左往右，设置选中。恢复上一个
            item->setColorMode(Rect::SELECTED);
            if(record->attribute2-1>=0&&itemList[record->attribute2-1]->rect->getColorMode()!=Rect::PIVOT&&itemList[record->attribute2-1]->rect->getColorMode()!=Rect::FINISHED)
                itemList[record->attribute2-1]->rect->setColorMode(Rect::NORMAL);
        case 6://从右往左，设置选中，回复上一个
            item->setColorMode(Rect::SELECTED);
            if(record->attribute2+1 < numItem&&itemList[record->attribute2+1]->rect->getColorMode()!=Rect::PIVOT&&itemList[record->attribute2+1]->rect->getColorMode()!=Rect::FINISHED)
                itemList[record->attribute2+1]->rect->setColorMode(Rect::NORMAL);
        case 7://已固定的轴值
            item->setColorMode(Rect::FINISHED);


        }
    }
    else
    {
        if(event->userMode==0)
            event->wholeTimer->start(400);
        int a1=record->attribute1,a2=record->attribute2;
         for(int i=a1;i<=a2;i++)
         {
             Rect * item = itemList[i]->rect;
             if(item->getColorMode()==Rect::NORMAL)
                item->setColorMode(Rect::SELECTED);
             else
                item->setColorMode(Rect::NORMAL);
         }
    }
}

MergeSort::~MergeSort()
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

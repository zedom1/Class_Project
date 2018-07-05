#include "widget.h"
#include "ui_widget.h"
#include "sortalgorithm.h"
#include "heapsort.h"
#include "selectionsort.h"
#include "quicksort.h"
#include "event.h"
#include "radixsort.h"
#include "bubblesort.h"
#include "mergesort.h"
#include "insertionsort.h"

Widget* Widget::w = NULL;

Widget * Widget::getInstance()
{
    if(!w){
        w = new Widget;
    }
    return w;
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(1200,700);
    setStyleSheet("background-color:white;");
    ui->num_text->setValidator(new QIntValidator(2,20,this));
    QRegExp regExp("[0-9 ,，]*");
    ui->array_text->setValidator(new QRegExpValidator(regExp,this));
    QObject::connect(this,SIGNAL(changeAlgo()),this,SLOT(receivemain()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::setTitle()
{
    switch(algomod){
    case 1:
        Event::getEvent()->view->setWindowTitle("Bubble Sort");

        ui->plainTextEdit->setPlainText("Bubble sort, sometimes referred to as sinking sort, is a simple sorting algorithm that repeatedly steps through the list to be sorted, compares each pair of adjacent items and swaps them if they are in the wrong order. The pass through the list is repeated until no swaps are needed, which indicates that the list is sorted. The algorithm, which is a comparison sort, is named for the way smaller or larger elements \"bubble\" to the top of the list. Although the algorithm is simple, it is too slow and impractical for most problems even when compared to insertion sort. Bubble sort can be practical if the input is in mostly sorted order with some out-of-order elements nearly in position.");
        break;
    case 2:
        Event::getEvent()->view->setWindowTitle("Selection Sort");
        ui->plainTextEdit->setPlainText("Selection sort has O(n2) time complexity. It divides the input list into two parts: the sublist of items already sorted, which is built up from left to right at the front (left) of the list, and the sublist of items remaining to be sorted that occupy the rest of the list. Initially, the sorted sublist is empty and the unsorted sublist is the entire input list. The algorithm proceeds by finding the smallest (or largest, depending on sorting order) element in the unsorted sublist, exchanging (swapping) it with the leftmost unsorted element (putting it in sorted order), and moving the sublist boundaries one element to the right.");
        break;
    case 3:
        Event::getEvent()->view->setWindowTitle("Insertion Sort");
        ui->plainTextEdit->setPlainText("Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until no input elements remain.");
        break;
    case 4:
        Event::getEvent()->view->setWindowTitle("Merge Sort");
        ui->plainTextEdit->setPlainText("An natural approach to problem solving is divide and conquer. In terms of sorting, we might consider breaking the list to be sorted into pieces, process the pieces, and then put them back together somehow. A simple way to do this would be to split the list in half, sort the halves, and then merge the sorted halves together. This is the idea behind Mergesort.");
        break;
    case 5:
        Event::getEvent()->view->setWindowTitle("Quick Sort");
        ui->plainTextEdit->setPlainText("Quicksort is aptly named because, when properly implemented, it is the fastest known general-purpose in-memory sorting algorithm in the average case. It does not require the extra array needed by Mergesort, so it is space efficient as well. Quicksort is widely used, and is typically the algorithmn implemented in a binary sort routine such as the UNIX qsort. Interestingly, Quicksort is hampered by exceedingly poor worst-case performance, thus making it inappropriate for certain applications.");
        break;
    case 6:
        Event::getEvent()->view->setWindowTitle("Heap Sort");
        ui->plainTextEdit->setPlainText("Heapsort is based on the heap data structure. First we use the heap building algorithm to convert the array into max-heap order. Then we repeatedly remove the maximum value from the heap, restoring the heap property each time that we do so, until the heap is empty. Heap is a balanced binary tree, and its array representation is space efficient. The asymptotic performance of Heapsort is θ(n log n) in the best, average, and worst cases.");
        break;
    case 7:
        Event::getEvent()->view->setWindowTitle("Radix Sort");
        ui->plainTextEdit->setPlainText("Radix sort is a non-comparative integer sorting algorithm that sorts data with integer keys by grouping keys by the individual digits which share the same significant position and value. ");
        break;
    }
}

void Widget::receivemain(){

    SortAlgorithm::getInstance()->resetAlgorithm(0,nullptr);
    this->setTitle();
    Event::getEvent()->view->show();

}

void Widget::reset()
{
    Event * event = Event::getEvent();
    event->userMode = 1;
    event->wholeTimer->stop();
    event->swapTimer->stop();
    event->view->hide();
    SortAlgorithm::getInstance()->remove();
    //algo->resetAlgorithm(0,nullptr,1);

}

void Widget::on_pushButton_8_clicked()
{
    reset();
    emit showmain();
}


void Widget::on_play_btn_clicked()
{
    Event * event = Event::getEvent();
    event->userMode = 1-event->userMode ;

    if(event->userMode==0){
        if(event->wholeTimer->isActive()==false)
            event->wholeTimer->start(100);
    }
    else
       event->wholeTimer->stop();
}

void Widget::on_next_btn_clicked()
{
    Event * event = Event::getEvent();
    event->userMode = 1;
    if(event->wholeTimer->isActive()==false)
        event->wholeTimer->start(100);
}

void Widget::on_restart_btn_clicked()
{
    Event * event = Event::getEvent();
    event->userMode = 1;
    event->wholeTimer->stop();

    SortAlgorithm::getInstance()->restart();

}

/*
 * 支持输入：
 *  1. 全随机，两个文本框均为空
 *  2. 部分随机：
 *      1. 给数组规模，元素未填
 *      2. 给元素，规模未填
 *      3. 给规模且给部分元素
 *  3. 全自定义：
 *      给数组规模和全部或超出规模的元素
 */

/*
 *  random  只支持最多输入数组规模
 *  reset   全支持
 */

void Widget::on_random_btn_clicked()
{
    int num=0;
    Event * event = Event::getEvent();
    event->userMode = 1;
    event->wholeTimer->stop();
    event->swapTimer->stop();

    if(ui->num_text->text().isEmpty()==false){
        num = ui->num_text->text().toInt();
    }
    SortAlgorithm::getInstance()->resetAlgorithm(num);
}

void Widget::on_reset_btn_clicked()
{
    int num=0;
    Event * event = Event::getEvent();
    event->userMode = 1;
    event->wholeTimer->stop();
    event->swapTimer->stop();
    int * array = nullptr ;
    if(ui->num_text->text().isEmpty()==false){
        num = ui->num_text->text().toInt();
    }
    if(ui->array_text->text().isEmpty()==false){
        array = new int[20];
        QStringList list = ui->array_text->text().split(QRegExp("[ ,，]"));
        int counter = 0, validlength = list.length(), tem;
        for(int i=0; i<list.length(); i++){
            tem = (list.at(i)).toInt();
            if(tem<100&&tem>=0)
                array[counter++] = tem;
            else
                validlength--;
        }
        for(;counter<num;counter++)
            array[counter] = qrand()%20+5;
        num = num==0? std::min(std::max(validlength,2),10):num;
    }
    SortAlgorithm::getInstance()->resetAlgorithm(num,array);
}






void Widget::on_selection_btn_clicked()
{
    reset();
    SortAlgorithm::setAlgorithm(SelectionSort::getInstance());
    algomod = 2;
    emit changeAlgo();
}

void Widget::on_radix_btn_clicked()
{
    reset();
    SortAlgorithm::setAlgorithm(RadixSort::getInstance());
    algomod = 7;
    emit changeAlgo();
}

void Widget::on_quick_btn_clicked()
{
    reset();
    SortAlgorithm::setAlgorithm(QuickSort::getInstance());
    algomod = 5;
    emit changeAlgo();
}

void Widget::on_merge_btn_clicked()
{
    reset();
    SortAlgorithm::setAlgorithm(MergeSort::getInstance());
    algomod = 4;
    emit changeAlgo();
}

void Widget::on_insertion_btn_clicked()
{
    reset();
    SortAlgorithm::setAlgorithm(InsertionSort::getInstance());
    algomod = 3;
    emit changeAlgo();
}

void Widget::on_heap_btn_clicked()
{
    reset();
    SortAlgorithm::setAlgorithm(HeapSort::getInstance());
    algomod = 6;
    emit changeAlgo();
}

void Widget::on_bubble_btn_clicked()
{
    reset();
    SortAlgorithm::setAlgorithm(BubbleSort::getInstance());
    algomod = 1;
    emit changeAlgo();
}






#include "heapsort.h"
#include "selectionsort.h"
#include "quicksort.h"
#include "bubblesort.h"
#include "insertionsort.h"
#include "mergesort.h"
#include "radixsort.h"
#include "widget.h"
#include <QApplication>
#include <QtWidgets>
/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    Widget *w = new Widget();
    QGraphicsView *view = new QGraphicsView;

    SortAlgorithm::setAlgorithm(MergeSort::getInstance(w));
    /* copy here:
     * Radixsort,Bubblesort,QuickSort
     * MergeSort,InsertionSort, SelectionSort
     * HeapSort
     *
    SortAlgorithm * algo = SortAlgorithm::getInstance();
    view->setScene(algo->scene);
    w->resize(1200,700);
    w->setStyleSheet("background-color:white;");

    view->show();

    return a.exec();
}
*/

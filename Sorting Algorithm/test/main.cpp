#include "selectionsort.h"
#include  "quicksort.h"
#include "mergesort.h"
#include "widget.h"
#include "rect.h"
#include <QApplication>
#include <QtWidgets>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    Widget *w = new Widget();
    QGraphicsView *view = new QGraphicsView;

    SortAlgorithm::setAlgorithm(MergeSort::getInstance(w));
    SortAlgorithm * algo = SortAlgorithm::getInstance();
    view->setScene(algo->scene);
    w->resize(1200,700);
    w->setStyleSheet("background-color:white;");

    view->show();

    return a.exec();
}

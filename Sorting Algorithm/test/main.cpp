#include "widget.h"
#include "rect.h"
#include "processor.h"
#include <QApplication>
#include <QtWidgets>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    Widget *w = new Widget();
    QGraphicsView *view = new QGraphicsView;
    Processor *op = Processor::getProcessor(w);

    w->resize(1200,700);
    w->setStyleSheet("background-color:white;");

    view->setScene(op->scene);

    view->show();

    return a.exec();
}

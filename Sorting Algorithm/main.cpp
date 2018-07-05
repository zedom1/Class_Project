#include "mainwindow.h"
#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    Widget *s = Widget::getInstance();
    Event * event = Event::getEvent();
    MainWindow w;
    w.show();

    QObject::connect(&w,SIGNAL(showsort()),s,SLOT(receivemain()));
    QObject::connect(s,SIGNAL(showmain()),&w,SLOT(receivesort()));

    return a.exec();
}

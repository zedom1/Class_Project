#ifndef EVENT_H
#define EVENT_H

#include <QTimer>

#include <QApplication>
#include <QtCore>
#include <QObject>
#include <QtWidgets>
#include <iostream>
#include <algorithm>

class Event: public QObject
{
private:
    Event();
    static Event * event;

public:
    static Event * getEvent();

    QTimer * swapTimer;
    QTimer * wholeTimer;
    QTimer * downTimer;
    QTimer * mergeTimer;
    int userMode;
    QGraphicsView * view;
    QGraphicsScene * scene;

    void resetScene();

private slots:
    void update();

};

#endif // EVENT_H

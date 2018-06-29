#ifndef EVENT_H
#define EVENT_H

#include <QTimer>


class Event
{
private:
    Event();

public:
    static Event * event;
    static Event * getEvent();

    QTimer * swapTimer;
    QTimer * wholeTimer;
    int userMode;
    //QTimer * wholeTimer2;


};

#endif // EVENT_H

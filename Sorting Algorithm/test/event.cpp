#include "event.h"

Event * Event::event = NULL;

Event::Event()
{
    swapTimer = new QTimer();
    wholeTimer = new QTimer();
    downTimer = new QTimer();
    mergeTimer = new QTimer();
    userMode = 1;
    //wholeTimer2 = new QTimer();
}

Event * Event::getEvent()
{
    if(event == NULL)
        event = new Event();
    return event;
}

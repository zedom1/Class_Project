#include "event.h"

Event * Event::event = NULL;

Event::Event()
{
    swapTimer = new QTimer();
    wholeTimer = new QTimer();
    userMode = 0;
    //wholeTimer2 = new QTimer();
}

Event * Event::getEvent()
{
    if(event == NULL)
        event = new Event();
    return event;
}

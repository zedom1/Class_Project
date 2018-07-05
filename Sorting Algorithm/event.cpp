#include "event.h"
#include "widget.h"
Event * Event::event = NULL;

Event::Event()
{
    swapTimer = new QTimer();
    wholeTimer = new QTimer();
    downTimer = new QTimer();
    mergeTimer = new QTimer();
    userMode = 1;
    std::cout<<"Create Event"<<std::endl;
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,1200,700);
    scene->addWidget(Widget::getInstance());
    connect(scene, &QGraphicsScene::changed, this, &Event::update);
    view = new QGraphicsView;
    view->setScene(scene);
}

void Event::resetScene()
{
    if(scene)
        delete scene;
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,1200,700);
    scene->addWidget(Widget::getInstance());
    connect(scene, &QGraphicsScene::changed, this, &Event::update);
    view->setScene(scene);
}

Event * Event::getEvent()
{
    if(event == NULL)
        event = new Event();
    return event;
}

void Event::update()
{
    this->scene->update(this->scene->sceneRect());
}

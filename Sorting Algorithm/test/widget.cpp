#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_play_btn_clicked()
{
    Event * event = Event::getEvent();
    event->userMode = 0;
    event->wholeTimer->start(100);
}

void Widget::on_next_btn_clicked()
{
    Event * event = Event::getEvent();
    event->userMode = 1;
    event->wholeTimer->start(100);
}

void Widget::on_pause_btn_clicked()
{
    Event * event = Event::getEvent();
    event->userMode = 1;
}

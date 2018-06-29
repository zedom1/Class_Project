#include "widget.h"
#include "ui_widget.h"
#include "processor.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->num_text->setValidator(new QIntValidator(2,50,this));
    QRegExp regExp("[0-9 ,，]*");
    ui->array_text->setValidator(new QRegExpValidator(regExp,this));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_play_btn_clicked()
{
    Event * event = Event::getEvent();
    event->userMode = 0;
    if(event->wholeTimer->isActive()==false)
        event->wholeTimer->start(100);
}

void Widget::on_next_btn_clicked()
{
    Event * event = Event::getEvent();
    event->userMode = 1;
    if(event->wholeTimer->isActive()==false)
        event->wholeTimer->start(100);
}

void Widget::on_pause_btn_clicked()
{
    Event * event = Event::getEvent();
    event->userMode = 1;
}

/*
 * 支持输入：
 *  1. 全随机，两个文本框均为空
 *  2. 部分随机：
 *      1. 给数组规模，元素未填
 *      2. 给元素，规模未填
 *      3. 给规模且给部分元素
 *  3. 全自定义：
 *      给数组规模和全部或超出规模的元素
 */

/*
 *  random  只支持最多输入数组规模
 *  reset   全支持
 */

void Widget::on_random_btn_clicked()
{
    int num=0;

    if(ui->num_text->text().isEmpty()==false){
        num = ui->num_text->text().toInt();
    }
    Processor::getProcessor()->resetProcessor(num);
}

void Widget::on_reset_btn_clicked()
{
    int num=0;
    int * array = nullptr ;
    if(ui->num_text->text().isEmpty()==false){
        num = ui->num_text->text().toInt();
    }
    if(ui->array_text->text().isEmpty()==false){
        array = new int[20];
        QStringList list = ui->array_text->text().split(QRegExp("[ ,，]"));
        int counter = 0, validlength = list.length(), tem;
        for(int i=0; i<list.length(); i++){
            tem = (list.at(i)).toInt();
            if(tem<100&&tem>=0)
                array[counter++] = tem;
            else
                validlength--;
        }
        for(;counter<num;counter++)
            array[counter] = qrand()%20+5;
        num = num==0? std::min(std::max(validlength,2),10):num;
    }
    Processor::getProcessor()->resetProcessor(num,array);
}

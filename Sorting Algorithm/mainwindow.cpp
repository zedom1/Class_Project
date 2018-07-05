#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "heapsort.h"
#include "selectionsort.h"
#include "quicksort.h"
#include "event.h"
#include "radixsort.h"
#include "bubblesort.h"
#include "mergesort.h"
#include "insertionsort.h"
#include <QApplication>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::receivesort(){
    this->show();
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    SortAlgorithm::setAlgorithm(BubbleSort::getInstance());
    Widget::getInstance()->algomod = 1;
    emit showsort();
}

void MainWindow::on_pushButton_2_clicked()
{

    this->hide();
    SortAlgorithm::setAlgorithm(SelectionSort::getInstance());
    Widget::getInstance()->algomod = 2;
    emit showsort();
}


void MainWindow::on_pushButton_3_clicked()
{
    this->hide();
    SortAlgorithm::setAlgorithm(InsertionSort::getInstance());
    Widget::getInstance()->algomod = 3;
    emit showsort();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->hide();
    Widget::getInstance()->algomod = 4;
    SortAlgorithm::setAlgorithm(MergeSort::getInstance());
    emit showsort();
}

void MainWindow::on_pushButton_5_clicked()
{
    this->hide();
    Widget::getInstance()->algomod = 5;
    SortAlgorithm::setAlgorithm(QuickSort::getInstance());
    emit showsort();
}

void MainWindow::on_pushButton_6_clicked()
{
    this->hide();
    Widget::getInstance()->algomod = 6;
    SortAlgorithm::setAlgorithm(HeapSort::getInstance());
    emit showsort();
}

void MainWindow::on_pushButton_7_clicked()
{
    this->hide();
    Widget::getInstance()->algomod = 7;
    SortAlgorithm::setAlgorithm(RadixSort::getInstance());
    emit showsort();
}
